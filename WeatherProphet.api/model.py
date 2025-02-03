import torch
from torch import nn

class Forecast(nn.Module):
    def __init__(self):
        super().__init__()

        self.layers = nn.Sequential(
            nn.Linear(in_features=5, out_features=8),
            nn.ReLU(True),
            nn.Linear(in_features=5, out_features=8),
            nn.ReLU(True),
            nn.Linear(in_features=5, out_features=8),
            nn.ReLU(True),
            nn.Linear(in_features=5, out_features=8),
        )

    def forward(self, x):
        return self.layers(x)