import os
import numpy as np

# data_dir = "/mnt/f/Dataset/RigNetv1/" # "F:/Dataset/RigNetv1/"
data_dir = "/mnt/d/Dataset/AutoRS/"
model_list = np.loadtxt(os.path.join(data_dir, "test_final.txt"), dtype=np.int32)
# skip = [3685, 1333, 2921, 17736, 9466, 1236, 14836, 17872, 1226, 7665, 3724, 16552, 10497, 14455, 9853, 14519, 142]
for model_id in model_list:
    if os.path.exists(os.path.join(data_dir, f"centaur/{model_id}.tgf")):
        continue
    print(model_id)
    os.system(f'./Demo/Demo {model_id} -data_dir {data_dir} -skel centaur')
    