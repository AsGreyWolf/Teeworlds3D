#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_image.h>
#include <string>
#include <memory>
#define GLEW_STATIC
#include <glew.h>
#include <tools/vmath.h>

enum TEXTURE_MODS {
	TEXTURE_ANISOTROPY = 0x01,
	TEXTURE_FILTERING = 0x02,
	TEXTURE_DEPTH = 0x04,
};

class Texture {
public:
	Texture(SDL_Surface *surface, int flags = 0);
	Texture(const GLvoid *pixels, int w, int h, int flags = 0);
	Texture(const Texture &second);
	Texture();
	virtual ~Texture();
	Texture &operator=(const Texture &second);
	operator GLuint() const { return *data; };

	void Bind() const;

	float aspect = 1;
	glm::vec2 size = glm::vec2(0, 0);
	int flags = 0;

private:
	class Data {
	public:
		Data();
		~Data();
		operator GLuint() const { return id; };

	private:
		GLuint id = 0;
	};
	typedef std::shared_ptr<Data> TextureDataPtr;
#define TextureDataPtr(a) std::make_shared<Data>(a);

	TextureDataPtr data;
};

#endif