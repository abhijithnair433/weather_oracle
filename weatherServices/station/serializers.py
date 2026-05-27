from rest_framework import serializers
from .models import SensorReading, WeatherPrediction



class SensorReadingSerializer(serializers.ModelSerializer):
    class Meta:
        model = SensorReading
        fields = ["id", "station", "temperature", "humidity", "barometric_pressure", "recorded_at"]


class WeatherPredictionSerializer(serializers.ModelSerializer):
    class Meta:
        model = WeatherPrediction
        fields = ["id", "station", "predicted_label", "confidence_score", "predicted_for", "created_at"]