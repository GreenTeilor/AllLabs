import sys

import numpy as np

if len(sys.argv) != 4:
    print('invalid parameters: python ' + sys.argv[0] + ' name mu sigma')
else:
    np.save(sys.argv[1], np.random.normal(float(sys.argv[2]), float(sys.argv[3]), 1000),False)
