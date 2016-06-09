#!/usr/bin/env python3

import pandas as pd
import numpy as np
import scipy.ndimage 

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from matplotlib.ticker import AutoMinorLocator
from matplotlib import colors

# set stylesheet
# should be present in matplotlib.get_configdir()/stylelib/$name.mplstyle
plt.style.use('base')

# single plot
class Block:

    def __init__(self, gridspec):

        self.gridspec_stuff = gridspec

    def block(self,
            row,
            col,
            data,
            yval='state',
            x_tickval=False,
            y_tickval=False,
            title="",
            xlab="",
            ylab="",
            zlim=(0,1),
            cmap="RdBu_r",
            label="A",
            label_loc=(0.04,0.45)):

        global plt

        subsub = data[['sAf','sAm','state']]

        # make pivot tables
        pivot_state = subsub.pivot_table(values=yval, index='sAf', columns='sAm')

        # make a meshgrid
        xo = pivot_state.columns.values
        yo = pivot_state.index.values
        x, y = np.meshgrid(xo, yo)

        ax = plt.subplot(
                self.gridspec_stuff[row, col]
                )

        print(data['sAm'].describe())

        ax.set_xlim((0,.5))
        ax.set_ylim((0,.5))

        if not x_tickval:
            plt.setp(ax.get_xticklabels(), visible=False)

        if not y_tickval:
            plt.setp(ax.get_yticklabels(), visible=False)

        # all the z-values for the different contours
        z = pivot_state.values

        norm = colors.BoundaryNorm([ 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5 ], cmap.N)
        # contourplots of sex ratio
        out_ssr = ax.contourf(x, y, z, cmap=cmap, norm=norm)

        # set minor ticks
        minor_locator = AutoMinorLocator(5)
        ax.xaxis.set_minor_locator(minor_locator)
        ax.yaxis.set_minor_locator(minor_locator)

        if xlab != "":
            ax.set_xlabel(xlab)

        if ylab != "":
            ax.set_ylabel(ylab)

        # contour line of the 50:50 sex-ratio
        if yval == "ssr" or yval == "psr":
            ax.contour(x,y,z, [0.5], colors='black',linewidths=1.3)

        if title != "":
            plt.title(title)


        plt.text(x=label_loc[0],y=label_loc[1], s=label,fontsize=15, ha="center", va="center", color="white")

        return(out_ssr)
