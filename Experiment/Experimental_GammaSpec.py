#!/usr/bin/env python
# coding: utf-8

# In[4]:


import numpy.random

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

from scipy.optimize import curve_fit


from math import *

from scipy.optimize import curve_fit

def efficiency(e): 
    E = numpy.log((8.415*10**2)/e)
    return numpy.exp(-5.018 + (8.753*10**(-1))*E + (1.474*10**(-1))*E**2 - (1.590*10**(-1))*E**3 + (8.997*10**(-2))*E**4 - (2.401*10**(-2))*E**5)

energies_keV = numpy.arange(0,2500)
print(efficiency(energies_keV))


matplotlib.pyplot.figure(dpi=100)
matplotlib.pyplot.plot(energies_keV, efficiency(energies_keV))
matplotlib.pyplot.xlabel('Energy (keV)')
matplotlib.pyplot.ylabel("Efficiency")
matplotlib.pyplot.grid(b=None, which='major', axis='both', color='grey', linestyle='-', linewidth=.2)
matplotlib.pyplot.show()

print(numpy.argmax(numpy.nan_to_num(efficiency(energies_keV))))


# In[3]:


# Num	ROI_Start	ROI_End	Peak_Centroid	Energy_keV	FWHM_keV	Net_Area	Net_Area_Ucert	Continuum_Counts
# 4 = energy
# 6 = area
# 7 = area uncertainty


#Energy (keV) Calc Sim 
energy_activity = numpy.loadtxt('Calc_Sim_Activities.txt',skiprows=1)
sim = 100000000
vol = 0.000125
actual = 9.61E+15
energy_activity[:,2] = energy_activity[:,2]*(actual/sim)



A_livetime =  345600
B_livetime =   518400
C_livetime =   604800
D_livetime =   247515.79
Eff_livetime =   86961.2

#live_times = numpy.loadtxt("/Users/jvl2xv/anaconda/AFRL_RV/Transmutation/Logan_Gamma/txt_output_fits/Live_times.txt",skiprows=0)
# Raw data from gamma vision: Num	ROI_Start	ROI_End	Peak_Centroid	Energy_keV	FWHM_keV	Net_Area	Net_Area_Ucert	Continuum_Counts
# no rad
a_fits = numpy.loadtxt("/Users/jvl2xv/anaconda/AFRL_RV/Transmutation/Logan_Gamma/txt_output_fits/A_GaAs_PeakFit.txt",skiprows=5)
# 10 krad
b_fits = numpy.loadtxt("/Users/jvl2xv/anaconda/AFRL_RV/Transmutation/Logan_Gamma/txt_output_fits/B_GaAs_PeakFit.txt",skiprows=5)
# 100 krad
c_fits = numpy.loadtxt("/Users/jvl2xv/anaconda/AFRL_RV/Transmutation/Logan_Gamma/txt_output_fits/C_GaAs_PeakFit.txt",skiprows=5)
# 1 Mrad
d_fits = numpy.loadtxt("/Users/jvl2xv/anaconda/AFRL_RV/Transmutation/Logan_Gamma/txt_output_fits/D_GaAs_PeakFit.txt",skiprows=5)


a_area_areaUncert = uncertainties.unumpy.uarray(a_fits[:,6],a_fits[:,7])
b_area_areaUncert = uncertainties.unumpy.uarray(b_fits[:,6],b_fits[:,7])
c_area_areaUncert = uncertainties.unumpy.uarray(c_fits[:,6],c_fits[:,7])
d_area_areaUncert = uncertainties.unumpy.uarray(d_fits[:,6],d_fits[:,7])



# In[6]:


# 6 = area
# 7 = area uncert

# GET DECAY RATE

a_activity_activityUncert = a_area_areaUncert/A_livetime
b_activity_activityUncert = b_area_areaUncert/B_livetime
c_activity_activityUncert = c_area_areaUncert/C_livetime
d_activity_activityUncert = d_area_areaUncert/D_livetime


print(sum(d_activity_activityUncert))

# SUBTRACT BACKGROUND
# initialize
b_activity_activityUncert_BGcorrected = b_activity_activityUncert
c_activity_activityUncert_BGcorrected = c_activity_activityUncert
d_activity_activityUncert_BGcorrected = d_activity_activityUncert



tolerance_voltage_for_match = 1.8
background_counter = 0
# for each background peak (sample a)
for background_centroid in a_fits[:,3]:
    other_counter = 0
    # for each actual sample
    for other_centroid in b_fits[:,3]:
        if (abs(background_centroid - other_centroid) < tolerance_voltage_for_match):
            b_activity_activityUncert_BGcorrected[other_counter] = b_activity_activityUncert[other_counter] - a_activity_activityUncert[background_counter]
            break
        other_counter = other_counter + 1
    other_counter = 0
    # for each actual sample
    for other_centroid in c_fits[:,3]:
        if (abs(background_centroid - other_centroid) < tolerance_voltage_for_match):
            c_activity_activityUncert_BGcorrected[other_counter] = c_activity_activityUncert[other_counter] - a_activity_activityUncert[background_counter]
            break
        other_counter = other_counter + 1
    other_counter = 0
    # for each actual sample
    for other_centroid in d_fits[:,3]:
        if (abs(background_centroid - other_centroid) < tolerance_voltage_for_match):
            d_activity_activityUncert_BGcorrected[other_counter] = d_activity_activityUncert[other_counter] - a_activity_activityUncert[background_counter]
            #print('matched it', a_fits[background_counter,4], 'keV')
        other_counter = other_counter + 1    
    background_counter = background_counter + 1
    
# INCORPORTATE EFFICIENCY

b_activity_activityUncert_BGcorrected_effCorrected = b_activity_activityUncert_BGcorrected/efficiency(b_fits[:,4])
c_activity_activityUncert_BGcorrected_effCorrected = c_activity_activityUncert_BGcorrected/efficiency(c_fits[:,4])
d_activity_activityUncert_BGcorrected_effCorrected = d_activity_activityUncert_BGcorrected/efficiency(d_fits[:,4])



# In[9]:


# Get the total experimental activity
counter = 0
for energy in d_fits[:,4]:
    
    print(energy, d_activity_activityUncert_BGcorrected_effCorrected[counter])
    
    # remove the 511
    if energy == 511.01:
        d_activity_activityUncert_BGcorrected_effCorrected[counter] = 0
        
    
    counter += 1


print('total experimental activity without the 511: ', sum(d_activity_activityUncert_BGcorrected_effCorrected))


# In[5]:


fig = matplotlib.pyplot.figure(dpi=300)
ax = fig.add_subplot(111)

es = d_fits[:,4]
vals = uncertainties.unumpy.nominal_values(d_activity_activityUncert_BGcorrected_effCorrected)



uncerts = uncertainties.unumpy.std_devs(d_activity_activityUncert_BGcorrected_effCorrected)
# plot
matplotlib.pyplot.bar(es,vals, yerr=uncerts,width=6,label=es)

counter = 0
for xy in zip(es,numpy.round(vals,1)): 
    if vals[counter] > .7:
        ax.annotate('(%s, %s)' % xy, xy=xy, textcoords='data',fontsize=5,color='black') 
    else:
        ax.annotate('(%s, %s)' % xy, xy=xy, textcoords='data',fontsize=4,color='black',alpha=0) 

    counter = counter + 1


es = c_fits[:,4]
vals = uncertainties.unumpy.nominal_values(c_activity_activityUncert_BGcorrected_effCorrected)
uncerts = uncertainties.unumpy.std_devs(c_activity_activityUncert_BGcorrected_effCorrected)
# plot
matplotlib.pyplot.bar(es,vals, yerr=uncerts,width=6,label=es)

es = b_fits[:,4]
vals = uncertainties.unumpy.nominal_values(b_activity_activityUncert_BGcorrected_effCorrected)
uncerts = uncertainties.unumpy.std_devs(b_activity_activityUncert_BGcorrected_effCorrected)
# plot
matplotlib.pyplot.bar(es,vals, yerr=uncerts,width=6,label=es)



matplotlib.pyplot.legend(['1000 krad','100 krad','10 krad'])
#matplotlib.pyplot.xlabel('Energy (keV)')
#matplotlib.pyplot.ylabel("Count Rate (Bq)")
matplotlib.pyplot.grid(b=None, which='major', axis='both', color='grey', linestyle='-', linewidth=.2)
matplotlib.pyplot.xlim([0,1250])
matplotlib.pyplot.show()








# In[15]:


filename = "/Users/jvl2xv/anaconda/AFRL_RV/Transmutation/FinalExprData_1Mrad_E_Count_Stdev.txt"

toPrint = numpy.zeros([len(vals),3])
toPrint[:,0] = d_fits[:,4]
toPrint[:,1] = uncertainties.unumpy.nominal_values(d_activity_activityUncert_BGcorrected_effCorrected)
toPrint[:,2] = uncertainties.unumpy.std_devs(d_activity_activityUncert_BGcorrected_effCorrected)

numpy.savetxt(filename, toPrint)


# In[ ]:




