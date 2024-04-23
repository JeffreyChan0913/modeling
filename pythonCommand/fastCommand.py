import os

def load() -> dict:
    with open('.env','r') as file:
        lines = file.readlines()
    d = {}
    for line in lines:
        key, value = line.strip().split('=')
        d[key] = value
    return d

def showenv(n=len(env)) -> None:
    for idx,val  in enumerate(env.items()):
        if idx < n:
            print(val)
        else:
            break

def ls() -> None:
    os.system("ls")

def lsalh() -> None:
    os.system("ls -alh")

def custls(custom_command:str) -> None:
    os.system("ls " + custom_command)

def tls() -> None:
    os.system("tree .")

def tlsalh() -> None:
    os.system("tree -alh")

def custtls(custom_command:str) -> None:
    os.system("tree " + custom_command)

def pwd() -> None:
    os.system("pwd")

def mv(path0:str, path1:str) -> None:
    os.system("mv " + path0 + " " + path1)

def rmfile(path:str) -> None:
    os.system("rm " + path) 

def touch(path: str) -> None:
    os.system(touch + " " + path)

env = load()
