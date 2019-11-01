import IGVCSimulator as sim
import time

env = sim.Environment()
env.LoadScenario('/media/john/5A506552506535C3/Users/John/Desktop/drawing.svg')
env.SetSimulationTimeStep(0.016)
action = sim.ActionSpace()
action.SteeringAngle = 0
action.VehicleSpeed = 1
while True:
    state = env.Step(action)
    env.Render()
    time.sleep(0.016)

    if state.test_ended:
        env.Reset()
