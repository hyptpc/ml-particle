# ==============HOW TO RUN==================
#   input: 2 features (mom, tof)
#   run the following command
#   python3 confusion_matrix.py <tof> <ene>(指定しない場合はn)
#   pthファイルがある場合、そのファイルを読み込んで学習を再開

#   last update: 2024/02/18
# ==========================================

import uproot3
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import confusion_matrix
from sklearn.utils.multiclass import unique_labels
from sklearn.metrics import accuracy_score
import sys

# ROOTファイルからデータを読み込む
if len(sys.argv) == 3:
    if sys.argv[1].isdigit() and sys.argv[2].isdigit():
        tof_option = int(sys.argv[1])
        energy_loss_option = int(sys.argv[2])
        # file = uproot3.open(f"/home/had/kohki/work/ML/create_rootfiles/output_digits_tof{tof_option}_ene{energy_loss_option}.root")
        file = uproot3.open(
            f"/home/had/kohki/work/ML/create_rootfiles/output_bigdata_tof{tof_option}_ene{energy_loss_option}.root")
    elif sys.argv[1].isdigit():
        tof_option = int(sys.argv[1])
        # file = uproot3.open(f"/home/had/kohki/work/ML/create_rootfiles/output_digits_tof{tof_option}.root")
        file = uproot3.open(
            f"/home/had/kohki/work/ML/create_rootfiles/output_bigdata_tof{tof_option}.root")
    elif sys.argv[2].isdigit():
        energy_loss_option = int(sys.argv[2])
        # file = uproot3.open(f"/home/had/kohki/work/ML/create_rootfiles/output_digits_ene{energy_loss_option}.root")
        file = uproot3.open(
            f"/home/had/kohki/work/ML/create_rootfiles/output_bigdata_ene{energy_loss_option}.root")
    else:
        print("Invalid arguments. Please provide either both numeric arguments or one numeric argument.")
        sys.exit(1)
else:
    print("Usage: python confusion_matrix.py <tof_option> <energy_loss_option>")
    sys.exit(1)

tree = file["tree"]

# ブランチからデータを取得
particle_data = tree.array("particle")
particle_ml_data = tree.array("particle_ML")

class_labels = {0: r"$P$", 1: r"$\pi$", 2: r"$K$"}

# 混同行列を計算
conf_matrix = confusion_matrix(particle_data, particle_ml_data)

# ヒートマップを作成
sns.heatmap(
    conf_matrix,
    annot=True,
    fmt="d",
    cmap="Blues",
    xticklabels=[class_labels[i] for i in unique_labels(particle_ml_data)],
    yticklabels=[class_labels[i] for i in unique_labels(particle_data)],
)

print(accuracy_score(particle_data, particle_ml_data))
plt.title("Confusion Matrix")
plt.xlabel("output")
plt.ylabel("input")
plt.show()
if sys.argv[1].isdigit() and sys.argv[2].isdigit():
    # plt.savefig(f"/home/had/kohki/work/ML/learn/figures/confusion_matrix/matrix_tof{tof_option}_ene{energy_loss_option}.png")
    plt.savefig(
        f"/home/had/kohki/work/ML/learn/figures/confusion_matrix_bigdata/matrix_tof{tof_option}_ene{energy_loss_option}.png")
elif sys.argv[1].isdigit():
    # plt.savefig(f"/home/had/kohki/work/ML/learn/figures/confusion_matrix/matrix_tof{tof_option}.png")
    plt.savefig(
        f"/home/had/kohki/work/ML/learn/figures/confusion_matrix_bigdata/matrix_tof{tof_option}.png")

elif sys.argv[2].isdigit():
    # plt.savefig(f"/home/had/kohki/work/ML/learn/figures/confusion_matrix/matrix_ene{energy_loss_option}.png")
    plt.savefig(
        f"/home/had/kohki/work/ML/learn/figures/confusion_matrix_bigdata/matrix_ene{energy_loss_option}.png")
