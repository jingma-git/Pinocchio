import numpy as np
import os

if __name__ == "__main__":
    data_dir = "/mnt/f/Dataset/RigNetv1"
    # data_dir = "/home/server/MaJing/Dataset/RigNet/data"
    model_list = np.loadtxt(os.path.join(data_dir, "test_final.txt"), dtype=np.int)

    for model_id in model_list:
        obj_path = os.path.join(data_dir, f"obj/{model_id}.obj")
        out_path = os.path.join(data_dir, f"manifold/{model_id}.obj")
        os.system(f'./manifold --input {obj_path} --output {out_path}')