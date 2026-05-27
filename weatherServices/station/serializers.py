from rest_framework import serializers
from .models import SensorReading



class SensorReadingSerializer(serializers.ModelSerializer):
    class Meta:
        model = SensorReading
        fields = ["id", "station", "temperature", "humidity", "barometric_pressure", "recorded_at"]
