import matplotlib.pyplot as plt
import numpy as np

import pykep as pk
from pykep.orbit_plots import plot_planet, plot_lambert
from pykep import AU, DAY2SEC

import plotting
import json


def load(visual_js):
    """Load the visualize file"""
    planets = list()
    transfers = list()

    if len(visual_js["Planets"]) != len(visual_js["Transfers"]) + 1:
        raise ValueError(f'The number of transfers and planets does NOT add up.')

    for p in visual_js["Planets"]:
        planets.append(plotting.Planet(p["Name"], p["At"], p["Coordinates"], p["Color"])) #TODO: Repeat p["Color"] again to use the same color for the orbit

    for idx, t in enumerate(visual_js["Transfers"]):
        transfers.append(plotting.Transfer(planets[idx], planets[idx + 1], t["Velocity"], t["Color"]))

    for i in range(1, len(planets)):
        if planets[i-1].at >= planets[i].at:
            raise ValueError(f'"At" time values at planets are not ordered. Incoherent')

    return planets, transfers


def visualize(planets, transfers):
    fig = plt.figure(figsize=(10, 8))
    ax3d = plt.subplot(1, 1, 1, projection='3d')
    ax3d.set_xlabel('X (AU)')
    ax3d.set_ylabel('Y (AU)')
    ax3d.set_zlabel('Z (AU)')

    # #TODO: 2D plot, PASS AS ARGUMENT IN THE PLOT CALL!
    fig = plt.figure(figsize=(6, 6))
    ax2d = plt.subplot(1, 1, 1)
    ax2d.set_xlabel('X (AU)')
    ax2d.set_ylabel('Y (AU)')
    ax2d.scatter(0, 0, s=50, marker='o', color='yellow', edgecolor='darkorange')

    v = list()
    for p in planets:
        p.plot(ax3d, ax2d)

    for t in transfers:
        t.plot(ax3d, ax2d)
        v.extend(t.v_evolution)
    x = np.linspace(planets[0].at, planets[-1].at, len(v))

    # SUN
    ax3d.scatter(0, 0, 0, s=50, marker='o', color='yellow', edgecolor='darkorange')
    #ax2d.legend()

    #FIXME: Speed plot
    fig = plt.figure(figsize=(10, 4))
    ax_v = plt.subplot(1, 1, 1)
    #ax_v.set_title("Velocity evolution")
    ax_v.set_ylabel("Speed (m/s)")
    ax_v.set_xlabel("Time (JD)")
    ax_v.plot(x, v)


    plt.show()



def main():
    """ Main call. All the file parsing and plotting"""
    try:
        with open('visuals/visualize.json', 'rb') as f:
            visual_js = json.load(f)
    except FileNotFoundError:
        with open('visualize_aux.json', 'rb') as f:
            visual_js = json.load(f)

    planets, transfers = load(visual_js)
    visualize(planets, transfers)


if __name__ == '__main__':
    pass
    main()
    # fig = plt.figure(figsize=(6, 4))
    # ax_f = plt.subplot(1, 1, 1)
    # ax_f.set_xlabel('Generation')
    # ax_f.set_ylabel('Best raw fitness')
    # ax_f.plot(fitnes1, label='50K Individuals')
    # ax_f.plot(fitnes2, label='15K Individuals')
    # ax_f.plot(fitnes3, label='1K Individuals')
    # ax_f.plot(fitnes4, label='0.5K Individuals')
    # ax_f.legend()
    # plt.show()
