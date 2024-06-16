import os

# Path to the folder containing PNG files
folder_path = 'cinematic'


# List all PNG files in the folder
png_files = [f for f in os.listdir(folder_path) if f.endswith('.png')]

# Sort the PNG files by their current names
png_files.sort()

# Determine the padding length for new names (e.g., if the highest number is 1000, padding should be 4)
padding_length = len(str(len(png_files)))

# Rename the files sequentially
for index, old_name in enumerate(png_files):
    new_name = f"output_{index+1}.png"
    os.rename(os.path.join(folder_path, old_name), os.path.join(folder_path, new_name))
    print(f"Renamed {old_name} to {new_name}")

print("All files renamed.")
