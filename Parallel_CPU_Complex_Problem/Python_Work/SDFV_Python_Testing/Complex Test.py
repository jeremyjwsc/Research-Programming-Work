import numpy as np

n = 51 #number of data points
# Suppose the real and imaginary parts are created independently
real_part = np.random.normal(size=n)
imag_part = np.random.normal(size=n)

# Create a complex array - the imaginary part will be equal to zero
z = np.array(real_part, dtype=complex)
# Now define the imaginary part:
z.imag = imag_part
print(z)