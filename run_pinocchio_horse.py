import os
import numpy as np

# data_dir = "/mnt/f/Dataset/RigNetv1/" # "F:/Dataset/RigNetv1/"
data_dir = "/mnt/d/Dataset/AutoRS/"
model_list = np.loadtxt(os.path.join(data_dir, "test_final.txt"), dtype=np.int32)
model_list = model_list[5:]
for model_id in model_list:
    if os.path.exists(os.path.join(data_dir, f"horse/{model_id}.tgf")):
        continue
    print(model_id)
    os.system(f'./Demo/Demo {model_id} -data_dir {data_dir} -skel horse')
    