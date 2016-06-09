#!/usr/bin/env python3

# encoding=utf8  

import sys, string, re
import pandas as pd
import numpy as np
import scipy.ndimage 

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import matplotlib.lines as mlines
import matplotlib.patches as mpatches
from matplotlib.ticker import AutoMinorLocator
from matplotlib import rcParams
from matplotlib import colors


############ aux funcs ############

def sniff_parline(filename):

    f = open(filename)
    fl = f.readlines()
    f.close()

    linerange = list(range(0,len(fl)))
    linerange.reverse()

    parline = -1

    for lineno in linerange:

        if re.match("^\d",fl[lineno]) != None:
            parline = lineno
            break

    assert parline >= 0

    return parline



############ init figure ############


import block
rcParams['text.usetex'] = True 
rcParams['font.family'] = 'sans-serif'
rcParams['text.latex.preamble'] = [
       r'\usepackage{siunitx}',   # i need upright \micro symbols, but you need...
       r'\sisetup{detect-all}',   # ...this to force siunitx to actually use your fonts
       r'\usepackage{helvet}',    # set the normal font here
       r'\usepackage{sansmath}',  # load up the sansmath so that math -> helvet
       r'\sansmath'               # <- tricky! -- gotta actually tell tex to use!
]  

# initialize fig
fig = plt.figure(figsize=(10,10))

# specify a grid with 3 rows and 2 columns
gs = gridspec.GridSpec(4, 4)

# initialize block object
b = block.Block(gs)

# to prevent strings from being abbreviated
pd.set_option('display.max_colwidth', -1)


############ data etc ############



# get the summary file of the autosomal runs
datafile_auto = "summary_autosomal.csv"
sub_auto = pd.read_csv(datafile_auto, sep=";", dtype={"file": str})

# get the summary file of the autosomal runs
datafile_x = "summary_x.csv"
sub_x = pd.read_csv(datafile_x, sep=";", dtype={"file": str})



the_colors = [ "black", "#5fc9ff", "#ff0000", "#808080", "#FEBE7F", "#DB6D23" ]
# http://stackoverflow.com/questions/9707676/defining-a-discrete-colormap-for-imshow-in-matplotlib 
cmap = colors.ListedColormap(the_colors)
#norm = 

hvals = [ 0.2, 0.5, 0.8 ]

# alphabet counter for the subplot labeling
alphabet_ctr = 0


# loop through all the dominance values
for idx, hval_i in enumerate(hvals):

    # set gridspec row and column
    row = 0
    col = idx

    # make data subset for the first row of the graph: autosomal, epsilon = 0
    sub_dat_h_auto = sub_auto[
            (sub_auto["hAf"] == hval_i) 
            &
            (sub_auto["em"] == -0.02) 
            &
            (sub_auto["ef"] == -0.02) 
            ]
    nrow = len(sub_dat_h_auto.index)
    assert(nrow == 1)

    # get the corresponding filename of the file actually containing the contents
    # from the summary file
    the_file = list(sub_dat_h_auto["file"])[0]

    print(the_file)

    parline = sniff_parline(the_file)

    # read in the csv file
    data = pd.read_csv(the_file, sep=";", nrows=parline)

    # plot the data subset for the autosomal case
    b.block(
            row=row,
            col=col,
            cmap=cmap, 
            data=data,
            y_tickval= col==0,
            x_tickval=row==3,
            label=string.ascii_uppercase[alphabet_ctr],
            title=r'$h=' + str(hval_i) + '$')

    alphabet_ctr += 1

    row = 1
    # make data subset for the 2nd row of the graph: x-linked, epsilon = 0
    sub_dat_h_x = sub_x[
            (sub_x["hAf"] == hval_i) 
            &
            (sub_x["em"] == -0.02) 
            &
            (sub_x["ef"] == -0.02) 
            ]
    nrow = len(sub_dat_h_x.index)

    print(nrow)

    if nrow == 1:

        # get the corresponding filename of the file actually containing the contents
        # from the summary file
        the_file = list(sub_dat_h_x["file"])[0]

        parline = sniff_parline(the_file)

        # read in the csv file
        data = pd.read_csv(the_file, sep=";",nrows=parline)

        # plot the data subset for the autosomal case
        b.block(
                row=row,
                col=col,
                cmap=cmap, 
                data=data,
                y_tickval= col==0,
                x_tickval=row==3,
                label=string.ascii_uppercase[alphabet_ctr])
    
    alphabet_ctr += 1





    row = 2
    
    # make data subset for the first row of the graph: autosomal, epsilon = 0
    sub_dat_h_auto = sub_auto[
            (sub_auto["hAf"] == hval_i) 
            &
            (sub_auto["em"] == -0.05) 
            &
            (sub_auto["ef"] == -0.05) 
            ]
    nrow = len(sub_dat_h_auto.index)
    assert(nrow == 1)

    # get the corresponding filename of the file actually containing the contents
    # from the summary file
    the_file = list(sub_dat_h_auto["file"])[0]

    parline = sniff_parline(the_file)

    # read in the csv file
    data = pd.read_csv(the_file, sep=";", nrows=parline)

    # plot the data subset for the autosomal case
    b.block(
            row=row,
            col=col,
            cmap=cmap, 
            data=data,
            y_tickval= col==0,
            x_tickval=row==3,
            label=string.ascii_uppercase[alphabet_ctr])

    alphabet_ctr += 1

    row = 3
    # make data subset for the 4th row of the graph: x-linked, epsilon = -0.02
    sub_dat_h_x = sub_x[
            (sub_x["hAf"] == hval_i) 
            &
            (sub_x["em"] == -0.05) 
            &
            (sub_x["ef"] == -0.05) 
            ]
    nrow = len(sub_dat_h_x.index)

    if nrow == 1:

        # get the corresponding filename of the file actually containing the contents
        # from the summary file
        the_file = list(sub_dat_h_x["file"])[0]

        parline = sniff_parline(the_file)

        # read in the csv file
        data = pd.read_csv(the_file, sep=";", nrows=parline)

        # plot the data subset for the autosomal case
        b.block(
                row=row,
                col=col,
                cmap=cmap, 
                data=data,
                y_tickval= col==0,
                x_tickval= row==3,
                label=string.ascii_uppercase[alphabet_ctr])
    
    alphabet_ctr += 1

# now make the legend....
# make custom legend, following http://matplotlib.org/users/legend_guide.html#proxy-legend-handles
black_part = mpatches.Patch(color=the_colors[0], label=r'Both loci polymorphic')
red_part = mpatches.Patch(color=the_colors[2], label=r'Fixation $A_{\mathrm{\>f}}$, $B_{\mathrm{\>f}}$' )
blue_part = mpatches.Patch(color=the_colors[1], label=r'Fixation $A_{\mathrm{m}}$, $B_{\mathrm{m}}$' )
grey_part = mpatches.Patch(color=the_colors[3], label=r'Polymorphism in one locus only' )
orange_part = mpatches.Patch(color=the_colors[4], label=r'Fixation $A_{\mathrm{\>f}}$, $B_{\mathrm{m}}$' )
brown_part = mpatches.Patch(color=the_colors[5], label=r'Fixation $A_{\mathrm{m}}$, $B_{\mathrm{\>f}}$' )

plt.legend(handles=[red_part, blue_part, black_part, grey_part, orange_part, brown_part],
        bbox_to_anchor=(4,1.0),
        fontsize=12)

# y-axis label
plt.figtext(x = -0.15,
        y = .6,
        s = r'Strength of additive selection in females, $s_{A_{\mathrm{f}}}=s_{B_{\mathrm{f}}}$',
        rotation=90,
        horizontalalignment='center',
        fontsize=15)

# x-axis label
plt.figtext(x = 0.6,
        y = -0.15,
        s = r'Strength of additive selection in males, $s_{A_{\mathrm{m}}}=s_{B_{\mathrm{m}}}$',
        horizontalalignment='center',
        fontsize=15)

label_side_x = .99

# indicating autosomal, no epistasis
plt.figtext(x = label_side_x,
        y = .95,
        s = r'Autosomal, $\varepsilon=0$',
        fontsize=15)

# indicating X-linked, no epistasis
plt.figtext(x = label_side_x,
        y = .75,
        s = r'X-linked, $\varepsilon=0$',
        fontsize=15)

# indicating autosomal, with epistasis
plt.figtext(x = label_side_x,
        y = .55,
        s = r'Autosomal, $\varepsilon=-0.02$',
        fontsize=15)

# indicating autosomal, with epistasis
plt.figtext(x = label_side_x,
        y = .25,
        s = r'X-linked, $\varepsilon=-0.02$',
        fontsize=15)


plt.tight_layout()
graphname = "overview_xlinked.pdf"
plt.savefig(graphname,format="pdf", bbox_inches="tight")

