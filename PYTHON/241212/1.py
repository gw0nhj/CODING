import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import Adam

# 데이터 생성 함수
def generate_data(n_samples):
    X = np.random.randint(2, size=(n_samples, 10))  # 1 또는 0의 입력값을 가지는 10개의 노드
    Y = (np.sum(X, axis=1) >= 6).astype(int)  # 6개 이상의 '1'이 있는 경우 1, 아니면 0
    return X, Y

# 데이터셋 생성
X, Y = generate_data(10000)

# 신경망 모델 설계
model = Sequential([
    Dense(10, input_shape=(10,), activation='sigmoid'),
    Dense(10, activation='sigmoid'),
    Dense(1, activation='sigmoid')
])

# 모델 컴파일
model.compile(optimizer=Adam(), loss='binary_crossentropy', metrics=['accuracy'])

# 모델 훈련
model.fit(X, Y, epochs=200, batch_size=32, verbose=1)

# 예측
predictions = model.predict(X[:10])

# 결과 출력
for i in range(10):
    print(f"입력: {X[i]} 실제 출력: {Y[i]} 예측된 출력: {np.round(predictions[i])}")
