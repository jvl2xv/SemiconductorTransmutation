#!/usr/bin/env python
# coding: utf-8

# In[5]:


##### import numpy.random

import scipy
import scipy.optimize
import scipy.constants
import math
import numpy 
import uncertainties
import uncertainties.unumpy 

import matplotlib.axes
import matplotlib.pyplot
import scipy.misc
import scipy.special
import scipy.stats
from random import *
from scipy.special import xlogy
import sys
from scipy.stats import norm
import pandas as pd

def is_number(series):
    counter = 0
    boolArray = numpy.zeros(len(series))
    for i in series:
        try:
            float(i)
            boolArray[counter] = True
        except ValueError:
            boolArray[counter] = False
        counter = counter + 1
    return boolArray

# time in days for MRad sample = 46 (sample D)
t = 60*60*24*46


import brewer2mpl

# brewer2mpl.get_map args: set name  set type  number of colors
bmap = brewer2mpl.get_map('Paired', 'qualitative', 10)
colors = bmap.mpl_colors


import sys
#!{sys.executable} -m pip install periodictable
from periodictable import *




shielding = []          # initialize an empty list
fracDiscarded = numpy.zeros(100)

n_per = 10000000

for i in numpy.arange(0,100):
    filepath = "/Users/jvl2xv/mountMIT_cluster_EOFE/SemiconductorTransmuation/semiconductorTransmutation-Build/Shielding_63MeV_10000000_pencil_p5mm1cm1cm" + str(i) +  ".txt"

    
    shielding_i = pd.read_csv(filepath, sep=" ", header=None, names=["mat", "eNum", "tNum", "particle","createTime"])
    print(shielding_i.shape)
    lenI = shielding_i.shape[0]
    lenF = shielding_i.shape[0]
    
    if (shielding_i['createTime'].dtype == 'object'):
        # get rid of error lines
        print(shielding_i[is_number(shielding_i['createTime'])==False])
        shielding_i = shielding_i[(is_number(shielding_i['createTime'])==True)]
        shielding_i = shielding_i[(is_number(shielding_i['createTime'])==True)]
        shielding_i = shielding_i[(is_number(shielding_i['createTime'])==True)]
        shielding_i['createTime'] = shielding_i['createTime'].astype(float)
        shielding_i['createTime'] = shielding_i['createTime'].astype(float)
        shielding_i['createTime'] = shielding_i['createTime'].astype(float)
        print(shielding_i.shape)
        lenF = shielding_i.shape[0]
        
    fracDiscarded[i] = lenF/lenI
    
    shielding_i_noDuplicates = shielding_i.drop(shielding_i[shielding_i.createTime > t].index)
    boolDups = shielding_i_noDuplicates.duplicated(subset=['mat','eNum','createTime'], keep='last')
    boolInstableSameTime = shielding_i_noDuplicates['particle'].str.contains("\[")
    #shielding_i_noDuplicates['keepForFission'] = and(boolDups,not(boolInstableSameTime))
    shielding_i_noDuplicates['eNum'][boolDups & ~boolInstableSameTime] = shielding_i_noDuplicates['eNum'][boolDups & ~boolInstableSameTime]*1000000
    shielding_i_noDuplicates = shielding_i_noDuplicates.drop_duplicates(subset=['mat','eNum'], keep='last')
    print(shielding_i_noDuplicates.shape)
    
    shielding_pivot = shielding_i_noDuplicates[['particle','mat']].pivot_table(index='particle', columns='mat', aggfunc=len, fill_value=0)
    filename = "/Users/jvl2xv/anaconda/AFRL_RV/Transmutation/Shielding_63MeV_100000000_pencil_p5mm1cm1cm_" + str(i) +  "_pivot.txt"
    #shielding_pivot.to_csv(filename,  sep=' ', mode='a')
    print('done with: ', i)



# In[61]:


# Read in the previously pivoted GEANT4 results

all_pivots = []
for i in numpy.arange(0,100):
    filename = "/Users/jvl2xv/anaconda/AFRL_RV/Transmutation/Shielding_63MeV_100000000_pencil_p5mm1cm1cm_" + str(i) +  "_pivot.txt"
    shielding_pivot_i = pd.read_csv(filename, sep=" ")
    shielding_pivot_i['nFile'] = i
    if 'G4_Galactic' in shielding_pivot_i.columns:
        del shielding_pivot_i['G4_Galactic']
    all_pivots.append(shielding_pivot_i)
    #print(shielding_pivot_i)

    
 
complete_pivots = pd.concat(all_pivots)
#print(complete_pivots)

#all_pivots_p = pd.DataFrame(complete_pivots, columns=["mat", "eNum", "tNum", "particle","createTime"])
total_pivot = complete_pivots.pivot_table(index='particle', aggfunc=sum, fill_value=0)  
#total_pivot.reset_index(level=0, inplace=True)
total_pivot['particle'] = total_pivot.index
total_pivot['particle'] = total_pivot['particle'].str.upper()
#df.groupby(['particle']).transform('sum')


total_pivot['Symbol'] = total_pivot.index.str.replace('[^a-zA-Z]', '').str.upper()
shielding_pivot_element = pd.pivot_table(total_pivot, index='Symbol', values=total_pivot.columns[0:8], aggfunc=sum, fill_value=0)

col_names = numpy.array(shielding_pivot_element.columns[0:8])
col_names = col_names.astype(str)

final_counts_by_material = numpy.zeros(shielding_pivot_element.shape)
element_symbols = shielding_pivot_element.index


for materialNum, column in enumerate(col_names):
    row_count = shielding_pivot_element[column]
    material_name = column.lower()
    for elemNum, symbol in enumerate(element_symbols):
        element_symbol = symbol.lower()
        if element_symbol in material_name:
            row_count[elemNum] = 0
    final_counts_by_material[:,materialNum] = row_count

# NOTE: final_counts_by_material contains the pivot by element by material with just the impurity elements

# SAVE THE RESULTS

dataframe_forSaving = pd.DataFrame(final_counts_by_material, columns=col_names)
dataframe_forSaving['Element_Symbol'] = element_symbols
filename = 'GEANT4_RESULTS_PIVOT_All_test.csv'
dataframe_forSaving.to_csv(filename, index=False)



# In[9]:


# FOR THE COMPARE TO EXPERIMENT FOR MONOENERGETICS 
# density in g/cc

density_HgCdTe = 7.43 
density_GaAs = 5.31
density_InAsSb = 5.67945 
density_InSbBi_5Bi = 6.64
density_InSbBi_05Bi = 5.87
density_InSb = 5.77
density_Si = 2.33
density_InAs = 5.68

# in cm^3, 1cm x 1cm x 0.5 mm (0.05 cm)
volume = 1*1*0.05

HgCdTe_massPercent = [46.5348,11.1763,42.2889]
InAsSb_massPercent = [59.19831,35.15173,5.649964]
InSbBi_highBi_massPercent = [40.97894,21.72824,37.29281]
InSbBi_lowBi_massPercent = [47.65443,48.00879,4.336783]
InAs_massPercent = [60.51349,39.48646]
InSb_massPercent = [48.53288, 51.46712]
GaAs_massPercent = [48.203,51.797]


# sample mass in kg
print('DENSITY (g/cc) |||| MASS (kg): |||| Mass %')
print('HgCdTe: ',density_HgCdTe, round(density_HgCdTe*volume/1000,10), HgCdTe_massPercent)
print('GaAs: ',density_GaAs, round(density_GaAs*volume/1000,10), GaAs_massPercent)
print('InAsSb: ',density_InAsSb, round(density_InAsSb*volume/1000,10), InAsSb_massPercent)
print('InSbBi_5Bi: ',density_InSbBi_5Bi, round(density_InSbBi_5Bi*volume/1000,10), InSbBi_highBi_massPercent)
print('InSbBi_05Bi: ', density_InSbBi_05Bi,round(density_InSbBi_05Bi*volume/1000,10), InSbBi_lowBi_massPercent)
print('InSb: ',density_InSb, round(density_InSb*volume/1000,10), InSb_massPercent)
print('Si: ', density_Si,round(density_Si*volume/1000,10), [1])
print('InAs: ',density_InAs, round(density_InAs*volume/1000,10), InAs_massPercent)


# In[10]:


# FOR THE ORBITAL SPECTRA RUNS
# density in g/cc

density_HgCdTe = 7.43 
density_GaAs = 5.31
density_InAsSb = 5.67945 
density_InSbBi_5Bi = 6.64
density_InSbBi_05Bi = 5.87
density_InSb = 5.77
density_Si = 2.33
density_InAs = 5.68

# in cm^3, 1cm x 1cm x 0.5 mm (0.05 cm)
volume = 1*1*1

HgCdTe_massPercent = [46.5348,11.1763,42.2889]
InAsSb_massPercent = [59.19831,35.15173,5.649964]
InSbBi_highBi_massPercent = [40.97894,21.72824,37.29281]
InSbBi_lowBi_massPercent = [47.65443,48.00879,4.336783]
InAs_massPercent = [60.51349,39.48646]
InSb_massPercent = [48.53288, 51.46712]
GaAs_massPercent = [48.203,51.797]


# sample mass in kg
print('DENSITY (g/cc) |||| MASS (kg): |||| Mass %')
print('HgCdTe: ',density_HgCdTe, round(density_HgCdTe*volume/1000,10), HgCdTe_massPercent)
print('GaAs: ',density_GaAs, round(density_GaAs*volume/1000,10), GaAs_massPercent)
print('InAsSb: ',density_InAsSb, round(density_InAsSb*volume/1000,10), InAsSb_massPercent)
print('InSbBi_5Bi: ',density_InSbBi_5Bi, round(density_InSbBi_5Bi*volume/1000,10), InSbBi_highBi_massPercent)
print('InSbBi_05Bi: ', density_InSbBi_05Bi,round(density_InSbBi_05Bi*volume/1000,10), InSbBi_lowBi_massPercent)
print('InSb: ',density_InSb, round(density_InSb*volume/1000,10), InSb_massPercent)
print('Si: ', density_Si,round(density_Si*volume/1000,10), [1])
print('InAs: ',density_InAs, round(density_InAs*volume/1000,10), InAs_massPercent)


# In[ ]:




