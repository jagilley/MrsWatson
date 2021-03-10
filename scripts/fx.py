import subprocess
import shlex
import time

xec_path = "/Volumes/GoogleDrive/My Drive/Drive Code/mwjg/bin/Mac OS X/mrswatson"

crypath = "/Volumes/GoogleDrive/My Drive/Ableton/Cry.wav"
alivepath = "/Volumes/GoogleDrive/My Drive/Drive Code/MrsWatson/bin/Mac OS X/alive44132.wav"

str1 = "mrswatson --input mysong.wav --output out.wav --plugin myplugin"

# to get parameters: ./mrswatson -p ValhallaRoom --display-info

def ValhallaRoom(mix=1):
    return f"ValhallaRoom --parameter 0,{mix}"

def OTT(mix=1):
    return f"OTT --parameter 0,{mix}"

def Vinyl(year=1):
    return f"Vinyl --parameter 13,{year}"

def processAudio(inpath, outpath, fxlist):
    ipsans = inpath.split(".")[0]
    for i, fx in enumerate(fxlist):
        if i == 0:
            cmdstr = f"{xec_path} --input {inpath} --output {ipsans}-{i}.wav --plugin " + fx
        else:
            cmdstr = f"{xec_path} --input {ipsans}-{(i-1)}.wav --output {ipsans}-{i}.wav --plugin " + fx
        subprocess.run(shlex.split(cmdstr), check=False)
        print("just ran")
        print(cmdstr)
        time.sleep(0.5)

processAudio("alive44132.wav", "out2.wav", [Vinyl(year=0)])