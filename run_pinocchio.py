import os
import numpy as np

data_dir = "F:/Dataset/RigNetv1"
model_list = np.loadtxt(os.path.join(data_dir, "test_final.txt"), dtype=np.int)

for model_id in model_list:
    os.system(f'./Demo/Demo {model_id}')