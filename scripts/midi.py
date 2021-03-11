import subprocess
import shlex
import time

xec_path = "/Volumes/GoogleDrive/My Drive/Drive Code/mwjg/bin/Mac OS X/mrswatson64"
saddest_of_all_keys = "resources/inputs/06 D Minor.mid"
outpath = "resources/outputs/"

# mrswatson --midi-file mysong.mid --output out.wav --plugin piano,soft.fxp

cmdstr = f"'{xec_path}' -p Serum -m '{saddest_of_all_keys}' -o {outpath}serum.wav"


subprocess.run(shlex.split(cmdstr), check=False)
print("Cmd just run was")
print(cmdstr)