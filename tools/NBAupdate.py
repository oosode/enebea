#!/usr/bin/env python

from time     import strptime
from datetime import datetime,timedelta
from glob     import glob 

Eastern=("TOR","PHI","NYK","BRK","BOS","CHI","IND","DET","CLE","MIL","MIA","ATL","WAS","ORL","CHO")
Western=("MIN","UTA","OKC","POR","DEN","GSW","SAC","LAC","PHO","LAL","HOU","SAS","DAL","NOP","MEM")

def readTeamHist(team,date):
  fin=open(team+"."+date+".hist.csv").readlines()

  wins       =[]
  loss       =[]
  pwins      =[]
  ploss      =[]
  oranks     =[]
  dranks     =[]
  league     =[]
  conference =[]
  division   =[]
  seeds      =[]
  lottery    =[]
  draftpos   =[]

  for i,line in enumerate(fin):
    if line.find("Wins")==0:
      tmp=fin[i+1].split(",")
     
      for l in range(0,len(tmp)-1):
        wins.append(tmp[l+1].rstrip("\n"))

    elif line.find("Loss")==0:
      tmp=fin[i+1].split(",")
      
      for l in range(0,len(tmp)-1):
        loss.append(tmp[l+1].rstrip("\n"))    
      
    elif line.find("pWins")==0:
      tmp=fin[i+1].split(",")

      for l in range(0,len(tmp)-1):
        pwins.append(tmp[l+1].rstrip("\n"))

    elif line.find("pLoss")==0:
      tmp=fin[i+1].split(",")
      
      for l in range(0,len(tmp)-1):
        ploss.append(tmp[l+1].rstrip("\n"))

    elif line.find("ORanks")==0:
      tmp=fin[i+1].split(",")
      
      for l in range(0,len(tmp)-1):
        oranks.append(tmp[l+1].rstrip("\n"))

    elif line.find("DRanks")==0:
      tmp=fin[i+1].split(",")

      for l in range(0,len(tmp)-1):
        dranks.append(tmp[l+1].rstrip("\n"))

    elif line.find("League")==0:
      tmp=fin[i+1].split(",")

      for l in range(0,len(tmp)-1):
        league.append(tmp[l+1].rstrip("\n"))

    elif line.find("Conference")==0:
      tmp=fin[i+1].split(",")

      for l in range(0,len(tmp)-1):
        conference.append(tmp[l+1].rstrip("\n"))

    elif line.find("Division")==0:
      tmp=fin[i+1].split(",")

      for l in range(0,len(tmp)-1):
        division.append(tmp[l+1].rstrip("\n"))

    elif line.find("Seeds")==0:
      tmp=fin[i+1].split(",")

      for l in range(0,len(tmp)-1):
        seeds.append(tmp[l+1].rstrip("\n"))

    elif line.find("Lottery")==0:
      tmp=fin[i+1].split(",")

      for l in range(0,len(tmp)-1):
        lottery.append(tmp[l+1].rstrip("\n"))

    elif line.find("DraftPos")==0:
      tmp=fin[i+1].split(",")

      for l in range(0,len(tmp)-1):
        draftpos.append(tmp[l+1].rstrip("\n"))

  HIST={}
  HIST["Wins"]=wins
  HIST["Loss"]=loss
  HIST["pWins"]=pwins
  HIST["pLoss"]=ploss
  HIST["ORanks"]=oranks
  HIST["DRanks"]=dranks
  HIST["League"]=league
  HIST["Conference"]=conference
  HIST["Division"]=division
  HIST["Seeds"]=seeds
  HIST["Lottery"]=lottery
  HIST["DraftPos"]=draftpos

  return HIST

def readDay(date,teams):
  
  globH={}
  for team in teams:
    h=readTeamHist(team,date)  
    globH[team]=h   

  return globH

def getTeams():

  teams=[]
  for f in glob("???.*hist.csv"):
    index=f.find(".")
    f=f[:index]
    if f not in teams:
      teams.append(f)

  print teams
  return teams

def getDate():
   
  return

def rolling(HIST,date):
  
  for key,value in HIST.items():
    teamPercent(key,value,date)

  return  

def teamPercent(team,hist,date):
 
  fileExist=False
  if glob(team+".career.csv"):
    fileExist=True

  fin=open(team+".career.csv","a")

  if not fileExist:
    for key,value in hist.items():
      fin.write(key+",")
      for i in range(len(value)):
        fin.write(str(i)+",")
      fin.write(",")
    fin.write("\n")

  for key,value in hist.items():
    fin.write(date+",")
    for v in value:
      fin.write(v+",")
    fin.write(",")

  fin.write("\n")  
  fin.close()  
  return


def run(begin,end):

  teams=getTeams()
  started=datetime(*strptime(begin,"%Y-%m-%d")[:6]).date()
  finished=datetime(*strptime(end,"%Y-%m-%d")[:6]).date()
  delta=finished-started

  for j in range(delta.days):

    opening=started+timedelta(days=0)
    closing=started+timedelta(days=j)

    if opening>closing:
      continue
 
    histograms=readDay(str(closing),teams)
    rolling(histograms,str(closing))
  
  snapshot(histograms,str(closing))
  return

def snapshot(HIST,date):
  
  fout=open("snapshot."+date+".csv","w")

  fout.write("Conf,TEAM,")
  fout.write("Lottery 1,Lottery 2,Lottery 3,Lottery 4,Lottery 5,Lottery 6,Lottery 7,")
  fout.write("Lottery 8,Lottery 9,Lottery 10,Lottery 11,Lottery 12,Lottery 13,Lottery 14,")
  fout.write("First Round,Semi Final,Conf. Final,Champ,")
  fout.write("Seed 1,Seed 2,Seed 3,Seed 4,Seed 5,Seed 6,Seed 7,Seed 8,")
  fout.write("Playoffs,\n")

  snapdict={}

  print "team"
  for team,dictionary in HIST.items():  
    snapdict[team]={}

    for k,v in dictionary.items():
    
      if k=="Seeds":
        seed1=float(v[0])
        seed2=float(v[1])
        seed3=float(v[2])
        seed4=float(v[3])
        seed5=float(v[4])
        seed6=float(v[5])
        seed7=float(v[6])
        seed8=float(v[7])

        p=seed1+seed2+seed3+seed4+seed5+seed6+seed7+seed8
        print team, p

      if k=="pWins":
        pw0=float(v[0])
        pw1=float(v[1])
        pw2=float(v[2])
        pw3=float(v[3])
        pw4=float(v[4])
        pw5=float(v[5])
        pw6=float(v[6])
        pw7=float(v[7])
        pw8=float(v[8])
        pw9=float(v[9])
        pw10=float(v[10])
        pw11=float(v[11])
        pw12=float(v[12])
        pw13=float(v[13])
        pw14=float(v[14])
        pw15=float(v[15])
        pw16=float(v[16])
        
	firs=pw16+pw15+pw14+pw13+pw12+pw11+pw10+pw9+pw8+pw7+pw6+pw5+pw4
	semi=pw16+pw15+pw14+pw13+pw12+pw11+pw10+pw9+pw8
	conf=pw16+pw15+pw14+pw13+pw12
	fina=pw16

        print team, fina, conf, semi, firs

      if k=="Lottery":
        lot1=float(v[0])
        lot2=float(v[1])
        lot3=float(v[2])
        lot4=float(v[3])
        lot5=float(v[4])
        lot6=float(v[5])
        lot7=float(v[6])
        lot8=float(v[7])
        lot9=float(v[8])
        lot10=float(v[9])
        lot11=float(v[10])
        lot12=float(v[11])
        lot13=float(v[12])
        lot14=float(v[13])

        print team, lot1, lot2, lot3, lot4, lot5, lot6, lot7, lot8      

    if team in Eastern:
      fout.write("East,%s,"%(team))
    else:
      fout.write("West,%s,"%(team))

    fout.write("%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,"%(lot1,lot2,lot3,lot4,lot5,lot6,lot7,lot8,lot9,lot10,lot11,lot12,lot13,lot14))
    fout.write("%.02f,%.02f,%.02f,%.02f,"%(firs,semi,conf,fina))
    fout.write("%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,%.02f,"%(seed1,seed2,seed3,seed4,seed5,seed6,seed7,seed8))
    fout.write("%.02f,\n"%(p))
    #print team,lot1,lot2,lot3,lot4,lot5,lot6,lot7,lot8,lot9,lot10,lot11,lot12,lot13,lot14,firs,semi,conf,fina,seed1,seed2,seed3,seed4,seed5,seed6,seed7,seed8,p

if __name__=="__main__":

  #getTeams()
  #readTeamHist("MIA","20131216")
  beg="2014-11-24"
  end="2014-11-25"
  run(beg,end)

