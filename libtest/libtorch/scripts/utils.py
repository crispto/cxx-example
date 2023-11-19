import colorsys


def generate_nice_colors(num_colors):
    # Generate a list of distinct colors
    hsv_colors = [(i / num_colors, 1.0, 1.0) for i in range(num_colors)]
    rgb_colors = [tuple(int(value * 255)
                        for value in colorsys.hsv_to_rgb(*hsv)) for hsv in hsv_colors]
    return rgb_colors


# Generate 80 nice colors
nice_colors = generate_nice_colors(80)
