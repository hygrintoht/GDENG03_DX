#include "meshObject.h"

#include "iostream"
#include "graphicsEngine.h"
#include "constantBuffer.h"
#include "engineTime.h"

meshObject::meshObject()
{
	
}

meshObject::meshObject(std::string file_path)
{
	loadObjFileData(file_path);
}

meshObject::~meshObject()
{
	
}

void meshObject::update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left)
{

	constant cc;
	cc.m_time = engineTime::get()->getRunningTimeAsMilliseconds();
	cc.m_world.setIdentity();

	if (m_animation_direction == 1 && m_animation_timer > 1.0f)
		m_animation_direction = -1;
	if (m_animation_direction == -1 && m_animation_timer < -1.0f)
		m_animation_direction = 1;

	m_animation_timer += engineTime::get()->getDeltaTime() * m_animation_direction;

	matrix4x4 transform;
	transform.setIdentity();

	switch (m_animation_type)
	{
		case 0:
			m_transform.setTranslation(vector3(m_transform.getTranslation().m_x, m_animation_timer, m_transform.getTranslation().m_z));
			break;
		case 1:
			transform.setRotationZ(m_animation_timer);
			cc.m_world *= transform;
			break;
		case 2:
			m_transform.setScale(vector3(0.1f, m_animation_timer * 0.1f, 0.1f));
			break;
		default:
			break;
	}

	cc.m_world *= m_transform;
	
	cc.m_view = world_camera_temp;

	int width = (right - left);
	int height = (bottom - top);

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	m_constant_buffer->update(graphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void meshObject::loadObjFileData(std::string file_path)
{
	std::string warn;
	std::string err;

	std::string basepath = "Assets/";
	std::string inputfile = basepath + file_path;

	//std::string inputfile = filePath;

	bool isSuccess = tinyobj::LoadObj
	(
		this->attrib,
		this->shapes,
		NULL,
		&warn,
		&err,
		inputfile.c_str()
	);
	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	std::cout << "Loaded " << file_path << std::endl;
	std::cout << "with # of shapes " << this->shapes->size() << std::endl;
	std::cout << "with # of vertices " << this->attrib->vertices.size() << std::endl;
	std::cout << "-------------------" << std::endl;

	loadObjDataToMemory();
}

void meshObject::loadObjDataToMemory()
{
	//std::vector<glm::vec3> vertices;
	//std::vector<GLuint> indices;

	for (int i = 0; i < this->attrib->vertices.size() / 3; i++) 
	{
		m_vertex_list.push_back
		(
			vertex
			{
				vector3
				{
				this->attrib->vertices[i * 3],		// x
				this->attrib->vertices[i * 3 + 1],	// y
				this->attrib->vertices[i * 3 + 2]	// z
				},
				vector3{1.0f,1.0f,1.0f},
				vector3{1.0f,1.0f,1.0f}
			}
		);
	}

	for (int i = 0; i < this->shapes->size(); i++) {
		tinyobj::shape_t shape = shapes->at(i);
		for (int j = 0; j < shape.mesh.indices.size(); j++) {
			unsigned int idx = shape.mesh.indices[j].vertex_index;
			m_index_list.push_back(idx);
		}
	}
}

void meshObject::changeAnimationType(int animation_type)
{
	m_animation_type = animation_type;
}
