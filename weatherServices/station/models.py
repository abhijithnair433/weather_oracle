from django.db import models

# Create your models here.


class Station(models.Model):
    name = models.CharField(max_length=100)
    location_desc = models.CharField(max_length=250)
    latitude = models.FloatField()
    longitude = models.FloatField()
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"station:{self.name} created at:{self.created_at}"

class SensorReading(models.Model):
    station = models.ForeignKey(Station, on_delete=models.CASCADE)
    temperature = models.FloatField()
    humidity = models.FloatField()
    barometric_pressure = models.FloatField()
    recorded_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"related to station:{self.station.name}  time:{self.recorded_at}"



class WeatherPrediction(models.Model):
    station = models.ForeignKey(Station, on_delete=models.CASCADE)
    predicted_label = models.CharField(max_length=250)
    confidence_score = models.FloatField()
    predicted_for = models.DateTimeField(blank=True, null=True)
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"related to station:{self.station.name} predicted:{self.predicted_label} time:{self.created_at}"
 

