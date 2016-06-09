#!/usr/bin/Rscript --vanilla

library("lattice")

args <- commandArgs(trailingOnly = T)

the.file <- args[[1]]

all.lines <- readLines(the.file)

nrow <- length(all.lines)

# start at the end of the file and work backwards
linerange <- rev(1:nrow)

parline <- -1

# get the line where the parameter description starts
for (line_i in linerange)
{
    if (length(grep("^type", all.lines[[line_i]])) == 1)
    {
        parline <- line_i-1
        break
    }
}

stopifnot(parline > 0)
rm(all.lines)


# read the parameters
pars <- read.table(the.file,skip = parline, sep=";")

# make string of parameters
parstr <- ""
for (row_i in 1:nrow(pars))
{
    parstr <- paste(parstr,pars[row_i,1],"=",pars[row_i,2],"\n",sep="")
}

# read the datafile
data <- read.table(the.file, header=T, nrow=parline-3, sep=";")

pdf(file=paste("graph_",basename(the.file),".pdf",sep=""),
        width=7,
        height=12
        )
print(levelplot(state ~ sAm * sAf,
                data=data,
                main=parstr,
                col.regions=c("black","blue","red","grey","orange","yellow"),
                at=c(0.5,1.5,2.5,3.5,4.5,5.5,6.5)
                )
        )
dev.off()
