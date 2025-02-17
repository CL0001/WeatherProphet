import torch.nn as nn
import torch.optim as optim

class WeatherPredictorLSTM(nn.Module):
    def __init__(self, input_size, hidden_size, num_layers, output_size):
        super(WeatherPredictorLSTM, self).__init__()
        self.lstm = nn.LSTM(input_size, hidden_size, num_layers, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        lstm_out, _ = self.lstm(x)
        output = self.fc(lstm_out[:, -1, :])
        return output

model = WeatherPredictorLSTM(input_size=4, hidden_size=64, num_layers=2, output_size=10)

criterion = nn.MSELoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)