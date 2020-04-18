import IGVCSimulator as sim
import time

env = sim.Environment()
env.LoadScenario('/media/john/5A506552506535C3/Users/John/Desktop/drawing.svg')
env.SetSimulationTimeStep(0.010)
action = sim.ActionSpace()
action.SteeringAngle = 0
action.VehicleSpeed = 1
counter = 0
while True:
    state = env.Step(action)
    if not env.Render():
        break
    time.sleep(0.016)

    if state.test_ended:
        env.Reset()
        
env.Close()