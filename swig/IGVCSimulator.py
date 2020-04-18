# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info >= (2, 7, 0):
    def swig_import_helper():
        import importlib
        pkg = __name__.rpartition('.')[0]
        mname = '.'.join((pkg, '_IGVCSimulator')).lstrip('.')
        try:
            return importlib.import_module(mname)
        except ImportError:
            return importlib.import_module('_IGVCSimulator')
    _IGVCSimulator = swig_import_helper()
    del swig_import_helper
elif _swig_python_version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_IGVCSimulator', [dirname(__file__)])
        except ImportError:
            import _IGVCSimulator
            return _IGVCSimulator
        try:
            _mod = imp.load_module('_IGVCSimulator', fp, pathname, description)
        finally:
            if fp is not None:
                fp.close()
        return _mod
    _IGVCSimulator = swig_import_helper()
    del swig_import_helper
else:
    import _IGVCSimulator
del _swig_python_version_info

try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr(self, class_type, name):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    raise AttributeError("'%s' object has no attribute '%s'" % (class_type.__name__, name))


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except __builtin__.Exception:
    class _object:
        pass
    _newclass = 0


def HelloWorld():
    return _IGVCSimulator.HelloWorld()
HelloWorld = _IGVCSimulator.HelloWorld

def run():
    return _IGVCSimulator.run()
run = _IGVCSimulator.run

def Step(action):
    return _IGVCSimulator.Step(action)
Step = _IGVCSimulator.Step
class Environment(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Environment, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Environment, name)
    __repr__ = _swig_repr

    def LoadScenario(self, filepath):
        return _IGVCSimulator.Environment_LoadScenario(self, filepath)

    def Step(self, action):
        return _IGVCSimulator.Environment_Step(self, action)

    def Render(self):
        return _IGVCSimulator.Environment_Render(self)

    def Close(self):
        return _IGVCSimulator.Environment_Close(self)

    def Reset(self):
        return _IGVCSimulator.Environment_Reset(self)

    def SetRewardGateValue(self, reward):
        return _IGVCSimulator.Environment_SetRewardGateValue(self, reward)

    def SetCrashRewardValue(self, reward):
        return _IGVCSimulator.Environment_SetCrashRewardValue(self, reward)

    def SetWindowSize(self, width, height):
        return _IGVCSimulator.Environment_SetWindowSize(self, width, height)

    def SetSimulationTimeStep(self, time_step):
        return _IGVCSimulator.Environment_SetSimulationTimeStep(self, time_step)

    def __init__(self):
        this = _IGVCSimulator.new_Environment()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _IGVCSimulator.delete_Environment
    __del__ = lambda self: None
Environment_swigregister = _IGVCSimulator.Environment_swigregister
Environment_swigregister(Environment)

class ActionSpace(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ActionSpace, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ActionSpace, name)
    __repr__ = _swig_repr
    __swig_setmethods__["VehicleSpeed"] = _IGVCSimulator.ActionSpace_VehicleSpeed_set
    __swig_getmethods__["VehicleSpeed"] = _IGVCSimulator.ActionSpace_VehicleSpeed_get
    if _newclass:
        VehicleSpeed = _swig_property(_IGVCSimulator.ActionSpace_VehicleSpeed_get, _IGVCSimulator.ActionSpace_VehicleSpeed_set)
    __swig_setmethods__["SteeringAngle"] = _IGVCSimulator.ActionSpace_SteeringAngle_set
    __swig_getmethods__["SteeringAngle"] = _IGVCSimulator.ActionSpace_SteeringAngle_get
    if _newclass:
        SteeringAngle = _swig_property(_IGVCSimulator.ActionSpace_SteeringAngle_get, _IGVCSimulator.ActionSpace_SteeringAngle_set)
    __swig_setmethods__["VehicleStopped"] = _IGVCSimulator.ActionSpace_VehicleStopped_set
    __swig_getmethods__["VehicleStopped"] = _IGVCSimulator.ActionSpace_VehicleStopped_get
    if _newclass:
        VehicleStopped = _swig_property(_IGVCSimulator.ActionSpace_VehicleStopped_get, _IGVCSimulator.ActionSpace_VehicleStopped_set)

    def __init__(self):
        this = _IGVCSimulator.new_ActionSpace()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _IGVCSimulator.delete_ActionSpace
    __del__ = lambda self: None
ActionSpace_swigregister = _IGVCSimulator.ActionSpace_swigregister
ActionSpace_swigregister(ActionSpace)

NUM_SENSORS = _IGVCSimulator.NUM_SENSORS
class StateSpace(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StateSpace, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StateSpace, name)
    __repr__ = _swig_repr
    __swig_setmethods__["VehicleSpeed"] = _IGVCSimulator.StateSpace_VehicleSpeed_set
    __swig_getmethods__["VehicleSpeed"] = _IGVCSimulator.StateSpace_VehicleSpeed_get
    if _newclass:
        VehicleSpeed = _swig_property(_IGVCSimulator.StateSpace_VehicleSpeed_get, _IGVCSimulator.StateSpace_VehicleSpeed_set)
    __swig_setmethods__["SteeringAngle"] = _IGVCSimulator.StateSpace_SteeringAngle_set
    __swig_getmethods__["SteeringAngle"] = _IGVCSimulator.StateSpace_SteeringAngle_get
    if _newclass:
        SteeringAngle = _swig_property(_IGVCSimulator.StateSpace_SteeringAngle_get, _IGVCSimulator.StateSpace_SteeringAngle_set)
    __swig_setmethods__["test_ended"] = _IGVCSimulator.StateSpace_test_ended_set
    __swig_getmethods__["test_ended"] = _IGVCSimulator.StateSpace_test_ended_get
    if _newclass:
        test_ended = _swig_property(_IGVCSimulator.StateSpace_test_ended_get, _IGVCSimulator.StateSpace_test_ended_set)
    __swig_setmethods__["reward"] = _IGVCSimulator.StateSpace_reward_set
    __swig_getmethods__["reward"] = _IGVCSimulator.StateSpace_reward_get
    if _newclass:
        reward = _swig_property(_IGVCSimulator.StateSpace_reward_get, _IGVCSimulator.StateSpace_reward_set)
    __swig_setmethods__["distances"] = _IGVCSimulator.StateSpace_distances_set
    __swig_getmethods__["distances"] = _IGVCSimulator.StateSpace_distances_get
    if _newclass:
        distances = _swig_property(_IGVCSimulator.StateSpace_distances_get, _IGVCSimulator.StateSpace_distances_set)

    def __init__(self):
        this = _IGVCSimulator.new_StateSpace()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _IGVCSimulator.delete_StateSpace
    __del__ = lambda self: None
StateSpace_swigregister = _IGVCSimulator.StateSpace_swigregister
StateSpace_swigregister(StateSpace)

# This file is compatible with both classic and new-style classes.

