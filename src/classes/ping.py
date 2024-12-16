from classes.communication import Communication
from classes.gameMode import RedLightGreenLight, AtYourCommand, LightTracker, MemoChain, SandBox, PING, BattleRoyale

class Ping:
    def __init__(self):
        self.communication = Communication()
        
    def run(self):
        pass
        
    def __str__(self):
        return "Ping :\n" + self.communication.__str__()
    
p = Ping()

print(p)
    