from django.shortcuts import render
from django.conf import settings
# Create your views here.
from django.http import HttpResponse
from django.utils import timezone



from rest_framework import status
from rest_framework.decorators import api_view
from rest_framework.response import Response
from .serializers import SensorReadingSerializer
from .models import SensorReading




@api_view(["POST", "GET"])
def readings(request):
    if request.method == "POST":
        serializer = SensorReadingSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    elif request.method == "GET":
        station_id = request.query_params.get("station")
        query_data = SensorReading.objects.filter(station_id= station_id)
        serializer = SensorReadingSerializer(query_data,many=True)
        return Response(serializer.data, status=status.HTTP_200_OK)
        
