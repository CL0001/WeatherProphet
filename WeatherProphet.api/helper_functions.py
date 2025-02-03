from datetime import datetime, timezone
from database import CityData

def kelvin_to_celsius(kelvin):
    return round(kelvin - 273.15)


def timestamp_to_datetime(timestamp):
    return datetime.fromtimestamp(timestamp, tz=timezone.utc).strftime('%H:%M:%S')


def format_response(weather_data):
    return {
        "name": weather_data["name"],
        "lon": weather_data["coord"]["lon"],
        "lat": weather_data["coord"]["lat"],
        "weather_description": weather_data["weather"][0]["description"],
        "temp": kelvin_to_celsius(weather_data["main"]["temp"]),
        "feels_like": kelvin_to_celsius(weather_data["main"]["feels_like"]),
        "temp_min": kelvin_to_celsius(weather_data["main"]["temp_min"]),
        "temp_max": kelvin_to_celsius(weather_data["main"]["temp_max"]),
        "pressure": weather_data["main"]["pressure"],
        "humidity": weather_data["main"]["humidity"],
        "sea_level": weather_data["main"]["sea_level"],
        "wind_speed": weather_data["wind"]["speed"],
        "sunrise": timestamp_to_datetime(weather_data["sys"]["sunrise"]),
        "sunset": timestamp_to_datetime(weather_data["sys"]["sunset"]),
    }


def format_query(city_record):
    return {
        "name": city_record.name,
        "lon": city_record.lon,
        "lat": city_record.lat,
        "weather_description": city_record.weather_description,
        "temp": city_record.temperature,
        "feels_like": city_record.feels_like,
        "temp_min": city_record.min_temperature,
        "temp_max": city_record.max_temperature,
        "pressure": city_record.pressure,
        "humidity": city_record.humidity,
        "sea_level": city_record.sea_level,
        "wind_speed": city_record.wind_speed,
        "sunrise": city_record.sunrise,
        "sunset": city_record.sunset,
    }

def format_for_database(weather_data):
    return CityData(
        name=weather_data["name"],
        lon=weather_data["lon"],
        lat=weather_data["lat"],
        weather_description=weather_data["weather_description"],
        temperature=weather_data["temp"],
        feels_like=weather_data["feels_like"],
        min_temperature=weather_data["temp_min"],
        max_temperature=weather_data["temp_max"],
        pressure=weather_data["pressure"],
        humidity=weather_data["humidity"],
        sea_level=weather_data["sea_level"],
        wind_speed=weather_data["wind_speed"],
        sunrise=weather_data["sunrise"],
        sunset=weather_data["sunset"],
        created_at=datetime.now(timezone.utc)
    )