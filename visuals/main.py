import matplotlib.pyplot as plt
import plotting
import json


def load(visual_js):
    """Load the visualize file"""
    planets = list()
    transfers = list()

    if len(visual_js["Planets"]) != len(visual_js["Transfers"]) + 1:
        raise ValueError(f'The number of transfers and planets does NOT add up.')

    for p in visual_js["Planets"]:
        planets.append(plotting.Planet(p["Name"], p["At"], p["Coordinates"], p["Color"]))

    for idx, t in enumerate(visual_js["Transfers"]):
        transfers.append(plotting.Transfer(planets[idx], planets[idx + 1], t["Velocity"], t["Color"]))

    for i in range(1, len(planets)):
        if planets[i-1].at >= planets[i].at:
            raise ValueError(f'"At" time values at planets are not ordered. Incoherent')

    return planets, transfers


def visualize(planets, transfers):
    fig = plt.figure(figsize=(10, 8))
    ax = plt.subplot(1, 1, 1, projection='3d')
    ax.set_xlabel('X (AU)')
    ax.set_ylabel('Y (AU)')
    ax.set_zlabel('Z (AU)')

    for p in planets:
        p.plot(ax)

    for t in transfers:
        t.plot(ax)

    # SUN
    ax.scatter(0, 0, 0, s=50, marker='o', color='yellow', edgecolor='darkorange')
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
    main()
