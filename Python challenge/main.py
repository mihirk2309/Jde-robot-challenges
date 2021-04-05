import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import argparse
import json

def survival(x, y, universe):
    num_neighbours = np.sum(universe[x - 1 : x + 2, y - 1 : y + 2]) - universe[x, y]
    # The rules of Life
    if universe[x, y] and not 2 <= num_neighbours <= 3:
        return 0
    elif num_neighbours == 3:
        return 1
    return universe[x, y]


def generation(frameNum, img, universe):
    new_universe = np.copy(universe)
    # Apply the survival function to every cell in the universe
    for i in range(universe.shape[0]):
        for j in range(universe.shape[1]):
            new_universe[i, j] = survival(i, j, universe)
    
    img.set_data(new_universe)
    universe[:] = new_universe[:]
    return img,


def animate_life(
    universe_size,
    seed,
    seed_position,
    quality=200,
    cmap="Purples",
    n_generations=50,
    interval=300,
    save=False,
):

    f = open('config.json',)
    data = json.load(f)
    seeds = data

    universe = np.zeros(universe_size)
    x_start, y_start = seed_position[0], seed_position[1]
    seed_array = np.array(seeds['seeds'][seed])
    x_end, y_end = x_start + seed_array.shape[0], y_start + seed_array.shape[1]
    universe[x_start:x_end, y_start:y_end] = seed_array

    fig, ax = plt.subplots()
    img = ax.imshow(universe, interpolation='nearest')
    ani = animation.FuncAnimation(fig, generation, fargs=(img, universe, ),
                                  frames = 10,
                                  interval=interval,
                                  save_count=50)

    plt.show()

if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        description="PyGameofLife. By default, produces 50 generations of the 'infinite' seed"
    )
    parser.add_argument("--universe-size", type=str, default="100,100")
    parser.add_argument("-seed", type=str, default="diehard")
    parser.add_argument("-quality", type=int, default=100)
    parser.add_argument("-interval", type=int, default=50)
    parser.add_argument("--seed-position", type=str, default="40,40")

    args = parser.parse_args()

    animate_life(
        universe_size=(
            int(args.universe_size.split(",")[0]),
            int(args.universe_size.split(",")[1]),
        ),
        seed=args.seed,
        quality=args.quality,
        seed_position=(
            int(args.seed_position.split(",")[0]),
            int(args.seed_position.split(",")[1]),
        ),
        interval=args.interval,
        save=True,
    )
