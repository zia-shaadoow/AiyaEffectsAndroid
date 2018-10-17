#ifndef AIYATRACK_H
#define AIYATRACK_H
#include <string>
#include <functional>
#include "FaceData.h"


namespace AiyaTrack
{
enum ImageType {
  tImageTypeNone,
  tImageTypeY,
  tImageTypeRGBA,
};

class FaceTrack
{
public:
	FaceTrack();
	FaceTrack(const std::string &s);
	virtual ~FaceTrack();

	virtual bool loadModel(const std::string &model, int min_face_size);
	virtual int track(uint8_t *image, int width, int height, ImageType type, FaceData *fd);
	virtual int trackAsync(uint8_t *image, int width, int height, ImageType type, FaceData *fd);

	std::function<void(int type, int ret, const char *info)> message;


private:
	bool isInit() const;
	void start(void *data);
	int stop();

	void sendImage(void *p);
	int getResult(FaceData *fd) const;

	void *receiveImage();
	void setResult(const FaceData &fd, int r);

	void setWidth(int w);
	void setHeight(int h);
	void setImageType(ImageType t);
	int getWidth() const;
	int getHeight() const;
	ImageType getImageType() const;
	void *createImageBuffer();

	int width;
	int height;
	uint8_t *trackImage;
	uint8_t *imgdata;
	int imageNumber;
	FaceData trackData;
	int trackResult;
	std::string modelPath;
	bool isLoaded;
	ImageType type;

friend void *TrackThreadLoop(void *data);

};

}

#endif
