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

    times = visual_js["Extra"]

    return planets, transfers, times


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


def animate(planets, transfers, times):
    fig = plt.figure(figsize=(6, 6))
    ax2d = plt.subplot(1, 1, 1)
    ax2d.set_xlabel('X (AU)')
    ax2d.set_ylabel('Y (AU)')
    ax2d.scatter(0, 0, s=50, marker='o', color='yellow', edgecolor='darkorange')

    for p in planets:
        p.plot_animate(ax2d)

    for n, t in enumerate(transfers):
        t.plot_animate(ax2d, planets, n)

def main():
    """ Main call. All the file parsing and plotting"""
    try:
        with open('visuals/visualize.json', 'rb') as f:
            visual_js = json.load(f)
    except FileNotFoundError:
        with open('visualize_aux.json', 'rb') as f:
            visual_js = json.load(f)

    planets, transfers, times = load(visual_js)
    visualize(planets, transfers)
    # animate(planets, transfers, times)


if __name__ == '__main__':
    main()
    # fitnes1 = [9628.03,9509.65,9451.8,9434.96,9433.26,9425.71,9416.53,9414.55,9413.61,9413.58,9413.46,9413.36,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35,9413.35]
    # fitness_mean = [1.83001e+09,1.68018e+08,6.26807e+07,4.20129e+07,6.40118e+07,8.73446e+07,4.73442e+07,1.06771e+07,5.34376e+06,2.67713e+06,4.01043e+06,4.67714e+06,3.34378e+06,4.67714e+06,1.34373e+06,676922,10147.4,10100.6,10163.1,10154.3,1.34344e+06,10127.6,10076.2,10061.9,10155.6,10098.9,10135.7,10099.1,10101.1,10075.9,676732,676743,676751,10069.5,10178.8,10085,10056.4,676749,10107.4,10061.5,10114.7,10075,10117.7,10073.7,10087.4,676766,10062.3,676754,676747,10104.1]
    # fitness_mean_roulette = [1.78935e+09,2.31363e+08,1.8269e+08,1.20687e+08,1.16686e+08,1.16018e+08,8.73508e+07,8.26838e+07,6.73499e+07,7.60165e+07,5.20162e+07,5.80159e+07,4.86826e+07,5.86824e+07,3.9349e+07,4.00156e+07,4.4682e+07,4.13486e+07,4.53487e+07,2.73485e+07,4.00153e+07,3.53485e+07,3.46817e+07,4.2015e+07,3.66814e+07,3.00146e+07,3.33481e+07,2.3348e+07,4.20146e+07,3.40144e+07,3.33477e+07,3.1348e+07,3.06813e+07,2.93478e+07,3.40144e+07,3.53478e+07,3.00143e+07,4.06811e+07,2.66812e+07,3.20142e+07,3.93477e+07,3.46808e+07,4.00141e+07,3.13475e+07,3.4014e+07,4.46807e+07,2.93472e+07,2.86805e+07,3.53472e+07,4.13471e+07]
    # fig = plt.figure(figsize=(6, 3))
    # ax_f = plt.subplot(1, 1, 1)
    # ax_f.set_xlabel('Generation')
    # ax_f.set_ylabel('Mean population fitness')
    # #ax_f.plot(fitnes1, label='50K Individuals')
    # ax_f.plot(fitness_mean_roulette, label='Roulette')
    # ax_f.plot(fitness_mean, label='Tournament')
    # # ax_f.plot(fitnes4, label='0.5K Individuals')
    # ax_f.legend()
    # plt.show()
