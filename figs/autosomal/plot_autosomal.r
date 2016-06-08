#!/usr/bin/Rscript --vanilla

library("lattice")
library("colorRamps")

bound <- 0.01

if (!exists("the.data"))
{
    args <- commandArgs(trailingOnly=T)
    the.file <- args[[1]]
    nrows <- as.numeric(args[[2]])
    the.data <- read.table(the.file,sep=";",header=T, nrow=nrows)
    the.data$state <- NA

    the.data[the.data$pAmf >= bound & the.data$pAmf <= 1-bound & the.data$pBmf >= bound & the.data$pBmf <= 1-bound
                & the.data$pAmm >= bound & the.data$pAmm <= 1-bound & the.data$pBmm >= bound & the.data$pBmm <= 1-bound,"state"] <- 1


    the.data[the.data$pAmf > 1-bound & the.data$pBmf > 1-bound & the.data$pAmm > 1-bound & the.data$pBmm > 1-bound,"state"] <- 2


    the.data[the.data$pAff > 1-bound & the.data$pBff > 1-bound & the.data$pAfm > 1-bound & the.data$pBfm > 1-bound,"state"] <- 3
    the.data[(
                (the.data$pAff > 1-bound & the.data$pBff >= bound & the.data$pBff <= .98) | 
                (the.data$pBff > 1-bound & the.data$pAff >= bound & the.data$pAff <= .98)
             )& (
                (the.data$pAfm > 1-bound & the.data$pBfm >= bound & the.data$pBfm <= .98) | 
                (the.data$pBfm > 1-bound & the.data$pAfm >= bound & the.data$pAfm <= .98)
            ), "state"] <- 4
    the.data[(the.data$pAff > 1-bound & the.data$pBff < bound)
                &
            (the.data$pAfm > 1-bound & the.data$pBfm < bound),"state"] <- 5


    the.data[(the.data$pAff < bound & the.data$pBff > 1-bound)
                & 
                (the.data$pAfm < bound & the.data$pBfm > 1-bound),"state"] <- 6
}

pdf("overview_epistasis_pAmf.pdf")
print(levelplot(pAmf ~ sAm * sAf | hAm * hAf * em * ef,
                data=the.data,
                col.regions=matlab.like,
                #                col.regions=c("black","blue","red","grey"),
                strip=function(...,strip.levels) { strip.default(strip.levels=T,...) }
                )
)
dev.off()

pdf("overview_epistasis_pAmm.pdf")
print(levelplot(pAmm ~ sAm * sAf | hAm * hAf * em *ef,
                data=the.data,
                col.regions=matlab.like,
                #                col.regions=c("black","blue","red","grey"),
                strip=function(...,strip.levels) { strip.default(strip.levels=T,...) }
                )
)
dev.off()

pdf("overview_epistasis_pBmf.pdf")
print(levelplot(pBmf ~ sAm * sAf | hAm * hAf * em * ef,
                data=the.data,
                col.regions=matlab.like,
                #                col.regions=c("black","blue","red","grey"),
                strip=function(...,strip.levels) { strip.default(strip.levels=T,...) }
                )
)
dev.off()

pdf("overview_epistasis_pBmm.pdf")
print(levelplot(pBmm ~ sAm * sAf | hAm * hAf * em *ef ,
                data=the.data,
                col.regions=matlab.like,
                #                col.regions=c("black","blue","red","grey"),
                strip=function(...,strip.levels) { strip.default(strip.levels=T,...) }
                )
)
dev.off()

pdf("overview_epistasis.pdf",width=15,height=10)
print(levelplot(state ~ sAm * sAf | hAm * hAf * em * ef,
                data=the.data,
                col.regions=c("black","lightblue1","red","grey","orange","khaki1"),
                at=c(0.5,1.5,2.5,3.5,4.5,5.5,6.5),
                strip=function(...,strip.levels) { strip.default(strip.levels=T,...) }
                )
)
dev.off()
