#!/usr/bin/env python

from time     import strptime,sleep
from datetime import datetime,timedelta
from os       import system
from glob     import glob

def getTeams():
  teams=[]
  for t in glob("???.*hist.csv"):
    index=t.find(".")
    t=t[:index]
    if t not in teams:
      teams.append(t)
  
  return teams

def getDates():

  fin=open("info.inp").readlines()

  for i,line in enumerate(fin):
    if len(line.split())>0:
      if line.split()[0]=="season" and line.split()[1]=="update" and line.split()[2]=="begin":
        start=line.split()[3]
      elif line.split()[0]=="season" and line.split()[1]=="update" and line.split()[2]=="end":
        finish=line.split()[3]

        break

  started=datetime(*strptime(start,"%Y-%m-%d")[:6]).date()
  finishing_date=strptime(finish,"%Y-%m-%d")
  finished=datetime(*strptime(finish,"%Y-%m-%d")[:6]).date()

  return started,finished

#print finished
#print finished+timedelta(days=1)

def runSim(started,num):
    
  for j in range(num):
   
    sleep(60) 
#    sleep(1)

    opening=started+timedelta(days=0)
    closing=started+timedelta(days=j)

    if opening>closing:
      continue

    f="info."+str(closing)
    fout=open(f+".inp","w")
    fin=open("info.inp").readlines()
		
    for line in fin:
      if len(line.split())>0:
        if line.split()[0]=="season" and line.split()[1]=="update" and line.split()[2]=="end":
          fout.write("season update end   "+str(closing)+"\n")
        elif line.split()[0]=="season" and line.split()[1]=="update" and line.split()[2]=="begin":
          fout.write("season update begin 2013-10-29\n")
        else:
          fout.write(line)
      else:
        fout.write(line)

    fout.close()

    ierr=1
    while ierr: 
      ierr=system("../enebea.exe < "+f+".inp > "+f+".out")

    teams=getTeams()
    for team in teams:
      system("cp "+team+".hist.csv "+team+"."+str(closing)+".hist.csv")

  return

if __name__=="__main__":

  beg,end=getDates()
  delta=end-beg

  runSim(beg,delta.days)
