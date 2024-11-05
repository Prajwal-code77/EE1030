import subprocess
import matplotlib.pyplot as plt

# Run the C program and capture its output
result = subprocess.run(['./point_on_line'], capture_output=True, text=True)
output = result.stdout.strip().split()
Ax, Ay = float(output[0]), float(output[1])
Bx, By = float(output[2]), float(output[3])
Px, Py = float(output[4]), float(output[5])  # Renamed C to P

# Plotting
plt.plot([Ax, Bx], [Ay, By], 'k-', label='Line Segment AB')  # Line segment AB in black
plt.plot(Px, Py, 'bo', label='Point P')  # Point P in blue

# Label points with their coordinates
plt.text(Ax, Ay, f'A ({Ax:.1f}, {Ay:.1f})', fontsize=12, color='black', verticalalignment='bottom', horizontalalignment='right')
plt.text(Bx, By, f'B ({Bx:.1f}, {By:.1f})', fontsize=12, color='black', verticalalignment='bottom', horizontalalignment='left')
plt.text(Px, Py, f'P ({Px:.1f}, {Py:.1f})', fontsize=12, color='blue', verticalalignment='bottom', horizontalalignment='left')

# Adjusted limits to ensure all points are visible
plt.xlim(-1, 8)  # X-axis limits to include points A and B
plt.ylim(-8, 5)  # Y-axis limits to include points A and B

plt.axhline(0, color='black', linewidth=0.5, ls='--')
plt.axvline(0, color='black', linewidth=0.5, ls='--')
plt.grid(color='gray', linestyle='--', linewidth=0.5)
plt.title('Line Segment and Point on the Line')
plt.legend()
plt.show()
