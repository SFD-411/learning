import folium
import json
import pandas

# imports text file containing volcano information
volcs = pandas.read_csv("volcanoes.txt")
lats = list(volcs["LAT"])
longs = list(volcs["LON"])
name = list(volcs["NAME"])
stats = list(volcs["STATUS"])
elev = list(volcs["ELEV"])

# defines colors based on elevation of volcano
def colormac(el):
    if el < 1000:
        return 'green'
    elif 1000 < el < 2000 :
        return 'orange'
    else:
        return 'red'

# creates starting point and tiling of map
map = folium.Map(location=[40.1, -115.1], zoom_start=5, tiles = "Stamen Terrain")

# creates feature groups for the map
mfg = folium.FeatureGroup(name="Volcano Markers")
pfg = folium.FeatureGroup(name="Populations")

# creates markers on the map based on lat, lon and applies attributes
for lt, ln, nm, st, el in zip(lats, longs, name, stats, elev):
    mfg.add_child(folium.CircleMarker(location=[lt, ln], radius=8,popup=nm + " is a " + st + " Volcanoe and is " + str(int(el)) + " high!", fill_color=colormac(el), color='white', fill_opacity=.5))

# creates color coding for geometries based on populations of counties
pfg.add_child(folium.GeoJson(json.load(open('world.json', 'r', encoding='utf-8-sig')), style_function=lambda x: {'fillColor':'green'if x['properties']['POP2005'] < 10000000 else 'orange' if 10000000 <= x['properties']['POP2005'] < 130000000 else 'red'}))

map.add_child(mfg)
map.add_child(pfg)
map.add_child(folium.LayerControl())

map.save("Map1.html")
