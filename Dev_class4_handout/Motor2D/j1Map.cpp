#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map

	
	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	bool loadmap = true;

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		loadmap = FillMapInfo(map_file.child("map"));
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}

bool j1Map::FillMapInfo(pugi::xml_node& map_info)
{
	bool ret = true;

	p2SString orientation = map_info.attribute("orientation").as_string();

	if (orientation == "orthogonal")
		map.orientation = ORIENTATION::ORTHOGONAL;
	else if (orientation == "isometric")
		map.orientation = ORIENTATION::ISOMETRIC;
	else if (orientation == "hexagonal")
		map.orientation == ORIENTATION::HEXAGONAL;

	p2SString renderorder = map_info.attribute("renderorder").as_string();

	if (renderorder == "right-down")
		map.renderorder = RENDERORDER::RIGHT_DOWN;
	else if (renderorder == "right-up")
		map.renderorder = RENDERORDER::RIGHT_UP;
	else if (renderorder == "left-down")
		map.renderorder = RENDERORDER::LEFT_DOWN;
	else if (renderorder == "left-up")
		map.renderorder = RENDERORDER::LEFT_UP;

	map.width = map_info.attribute("width").as_uint();
	map.height = map_info.attribute("height").as_uint();
	map.tilewidth = map_info.attribute("tilewidht").as_uint();
	map.tileheight = map_info.attribute("tileheight").as_uint();

}


bool j1Map::FillTileSet()
{

}




