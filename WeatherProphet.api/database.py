from sqlalchemy import create_engine, Column, Integer, Float, String, DateTime, func
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base

DATABASE_URL = "sqlite:///forecasts.db"

engine = create_engine(DATABASE_URL, connect_args={"check_same_thread": False})

session = sessionmaker(bind=engine, autocommit=False, autoflush=False)

Base = declarative_base()

class CityData(Base):
    __tablename__ = "citydata"

    id = Column(Integer, primary_key=True, index=True)
    name = Column(String, index=True)
    lon = Column(Float)
    lat = Column(Float)
    sunrise = Column(String)
    sunset = Column(String)
    weather_description = Column(String)
    temperature = Column(Float)
    feels_like = Column(Float)
    min_temperature = Column(Float)
    max_temperature = Column(Float)
    pressure = Column(Float)
    humidity = Column(Integer)
    wind_speed = Column(Float)
    sea_level = Column(Integer)
    created_at = Column(DateTime, default=func.now())

Base.metadata.create_all(bind=engine)