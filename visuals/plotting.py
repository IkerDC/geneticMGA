import matplotlib.pyplot as plt
import numpy as np
import datetime

import pykep
import pykep as pk
from pykep.core import propagate_lagrangian


AU = 149597870691.0
N = 60
MU = 1.32712440018e+20
SEC2DAY = 1.1574074074074073e-05
DAY2SEC = 86400
JD2000 = 2451544.50000


class Planet:
    def __init__(self, name: str, at, coordinates=None, color='gray'):
        self.name = name
        self.at = at
        self.coordinates = coordinates
        self.color = color

        if self.name not in ['mercury', 'venus', 'earth', 'mars', 'jupiter', 'saturn', 'uranus', 'neptune']:
            raise Exception(f"Unknown solar system planet named {self.name}")

        if isinstance(self.at, str):
            try:
                self.at = datetime.datetime.strptime(self.at, "%Y-%m-%d")
                self.at = self.at.toordinal() + 1721424.5
            except ValueError:
                raise ValueError(f'"at" attribute has str format but the value is not of the date type: "%Y-%m-%d"')
        elif isinstance(self.at, (float, int)):
            if self.at < 1721424.5:
                raise ValueError('"at" attribute must be a valid Julian Date.')
        else:
            raise ValueError('invalid data type from "at" attribute, must be str, int or float.')

    def plot(self, ax):
        """Plot the planet's orbit and the location if the coordinates have been passed"""
        plnt = pk.planet.jpl_lp(self.name)
        T = plnt.compute_period(pk.epoch(self.at, julian_date_type="jd")) * SEC2DAY
        when = np.linspace(0, T, N)

        x = np.array([0.0] * N)
        y = np.array([0.0] * N)
        z = np.array([0.0] * N)
        print(self.at - JD2000)
        for i, day in enumerate(when):
            r, v = plnt.eph(pk.epoch(self.at - JD2000 + day))
            x[i] = r[0] / AU
            y[i] = r[1] / AU
            z[i] = r[2] / AU

        ax.plot(x, y, z, label=self.name, color=self.color)

        # Plot also the planet location if needed
        if self.coordinates is not None:
            ax.scatter(self.coordinates[0]/AU, self.coordinates[1]/AU, self.coordinates[2]/AU,
                       marker='o', alpha=0.8, color=self.color)


class Transfer:
    def __init__(self, planet_origin: Planet, planet_dest: Planet, velocity, color='teal'):
        self.planet_origin = planet_origin
        self.planet_dest = planet_dest
        self.velocity = velocity
        self.color = color

        if not isinstance(self.planet_origin, Planet) or not isinstance(self.planet_dest, Planet):
            raise ValueError(f'Planet origin and destination must be a reference to Planet type object')

    def plot(self, ax):
        """Plot the transfer between the planet of origin and the next one."""
        x = np.zeros(N, )
        y = np.zeros(N, )
        z = np.zeros(N, )

        r = self.planet_origin.coordinates
        t = (self.planet_dest.at - self.planet_origin.at) * DAY2SEC
        ts = t / (N - 1)

        v = self.velocity
        for i in range(N):
            x[i] = r[0] / AU
            y[i] = r[1] / AU
            z[i] = r[2] / AU
            r, v = propagate_lagrangian(r, v, ts, MU)

        ax.plot(x, y, z, color=self.color)


