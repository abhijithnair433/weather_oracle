from django.core.management.base import BaseCommand
from ...models import Station, SensorReading, WeatherPrediction

class Command(BaseCommand):
    help = "Runs rain predictions for all stations"

    def handle(self, *args, **kwargs):
        self.stdout.write("Running predictions...")
        import joblib
        import os

        model_path = os.path.join("ml", "rain_model.joblib")
        model = joblib.load(model_path)

        stationObjects = Station.objects.all()
        

        
        for station in stationObjects:
            firstReading = SensorReading.objects.filter(station_id=station.pk).order_by("-recorded_at").first()
            if firstReading == None:
                continue
            modelinputs = [[firstReading.temperature, firstReading.humidity, firstReading.barometric_pressure]]
            prediction = model.predict(modelinputs)
            proba = model.predict_proba(modelinputs)
            from django.utils import timezone
            from datetime import timedelta

            predicted_for = timezone.now() + timedelta(hours=1)

            if prediction[0] == 0:
                predict = WeatherPrediction.objects.create(station=station, predicted_label="no rain", confidence_score=proba[0][1], predicted_for=predicted_for)
            elif prediction[0] == 1:
                predict = WeatherPrediction.objects.create(station=station, predicted_label="rain", confidence_score=proba[0][1],predicted_for=predicted_for)
