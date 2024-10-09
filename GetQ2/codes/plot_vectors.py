import subprocess
import matplotlib.pyplot as plt

# Call the C program and capture its output
result = subprocess.run(['./vector_calculator'], capture_output=True, text=True)

# Print the full output for debugging
print("C Program Output:")
print(result.stdout)

# Process the output
lines = result.stdout.strip().split('\n')

try:
    normal_vector = eval(lines[0].strip().split(': ')[1])
    direction_vector = eval(lines[1].strip().split(': ')[1])
    
    line_points_str = lines[2].strip().split(': ')[1]

    # Format the line points string properly
    line_points_str = line_points_str.replace(" ", "").strip() + "]"  # Ensure it ends correctly
    line_points_str = f"[{line_points_str}"  # Add the opening bracket

    # Debug: Print the formatted line points string
    print(f"Formatted Line Points String: '{line_points_str}'")

    # Convert string to a list of tuples using eval
    line_points = eval(line_points_str)

    x_line, y_line = zip(*line_points)
    shifted_origin = [0, 2]

    # Create the plot
    plt.quiver(*shifted_origin, *normal_vector, color='r', angles='xy', scale_units='xy', scale=1, 
               width=0.01, headwidth=5, label='Normal Vector', pivot='middle')
    plt.quiver(*shifted_origin, *direction_vector, color='b', angles='xy', scale_units='xy', scale=1, 
               width=0.01, headwidth=5, label='Direction Vector', pivot='middle')

    plt.plot(x_line, y_line, 'k--', label='Line (x + y = 4)', alpha=0.5)  # Dashed line

    plt.xlim(-5, 5)
    plt.ylim(-5, 5)
    plt.axhline(0, color='black', linewidth=0.5, ls='--')
    plt.axvline(0, color='black', linewidth=0.5, ls='--')
    plt.grid()
    plt.title('Normal and Direction Vectors for the Line x + y = 4')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.legend()
    plt.gca().set_aspect('equal', adjustable='box')
    plt.show()

except Exception as e:
    print(f"Error processing output: {e}")

