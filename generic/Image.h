#ifndef _Image_h
#define _Image_h

#include "project.h"
#include "stdio.h"
#include "memory.h"
#include "ImageProcessing.h"
#include <iostream>

#ifndef MATLAB_FOUND
	#include <QString>
	#include "ImageIO.h"
#else
	#include "mex.h"
#endif

using namespace std;

// template class for image
template <class T>
class Image
{
protected:
	T* pData;
	int imWidth,imHeight,nChannels;
	int nPixels,nElements;
	bool IsDerivativeImage;
public:
	Image(void);
	Image(int width,int height,int nchannels=1);
	Image(const T& value,int _width,int _height,int _nchannels=1);
#ifndef MATLAB_FOUND
	Image(const QImage& image);
#endif
	Image(const Image<T>& other);
	~Image(void);
	virtual Image<T>& operator=(const Image<T>& other);

	virtual inline void computeDimension(){nPixels=imWidth*imHeight;nElements=nPixels*nChannels;};

	virtual void allocate(int width,int height,int nchannels=1);
	
	template <class T1>
	void allocate(const Image<T1>& other);

	virtual void clear();
	virtual void reset();
	virtual void copyData(const Image<T>& other);
	void setValue(const T& value);
	void setValue(const T& value,int _width,int _height,int _nchannels=1);
	
	template <class T1>
	void copy(const Image<T1>& other);

	void im2double();

	// function to access the member variables
	inline T*& data(){return pData;};
	inline const T*& data() const{return (const T*&)pData;};
	inline int width() const {return imWidth;};
	inline int height() const {return imHeight;};
	inline int nchannels() const {return nChannels;};
	inline int npixels() const {return nPixels;};
	inline int nelements() const {return nElements;};
	inline bool isDerivativeImage() const {return IsDerivativeImage;};
	bool IsFloat () const;

	template <class T1>
	bool matchDimension  (const Image<T1>& image) const;

	inline void setDerivative(bool isDerivativeImage=true){IsDerivativeImage=isDerivativeImage;};

	// function to move this image to another one
	template <class T1>
	void moveto(Image<T1>& image,int x,int y,int width=0,int height=0);

	// function of basic image operations
	virtual bool imresize(double ratio);
	template <class T1>
	void imresize(Image<T1>& result,double ratio);
	void imresize(int dstWidth,int dstHeight);

#ifndef MATLAB_FOUND
	virtual bool imread(const QString& filename);
	virtual void imread(const QImage& image);

	virtual bool imwrite(const QString& filename,int quality=100) const;
	virtual bool imwrite(const QString& filename,ImageIO::ImageType imagetype,int quality=100) const;
#else
	virtual bool imread(const char* filename) const {return true;};
	virtual bool imwrite(const char* filename) const {return true;};
#endif

	template <class T1>
	Image<T1> dx(bool IsAdvancedFilter=false) const;

	template <class T1>
	void dx(Image<T1>& image,bool IsAdvancedFilter=false) const;

	template<class T1>
	Image<T1> dy(bool IsAdvancedFilter=false) const;

	template <class T1>
	void dy(Image<T1>& image,bool IsAdvancedFilter=false) const;

	template <class T1>
	void GaussianSmoothing(Image<T1>& image,double sigma,int fsize) const;

	template <class T1>
	void smoothing(Image<T1>& image,double factor=4);

	template <class T1>
	Image<T1> smoothing(double factor=4);

	void smoothing(double factor=4);

	// funciton for filtering
	template <class T1>
	void imfilter(Image<T1>& image,double* filter,int fsize) const;

	template <class T1>
	Image<T1> imfilter(double* filter,int fsize);

	template <class T1>
	void imfilter_h(Image<T1>& image,double* filter,int fsize) const;

	template <class T1>
	void imfilter_v(Image<T1>& image,double* filter,int fsize) const;

	template <class T1>
	void imfilter_hv(Image<T1>& image,double* hfilter,int hfsize,double* vfilter,int vfsize) const;

	// function to desaturating
	template <class T1>
	void desaturate(Image<T1>& image) const;

	template <class T1>
	void collapse(Image<T1>& image) const;

	// function to concatenate images
	template <class T1,class T2>
	void concatenate(Image<T1>& destImage,const Image<T2>& addImage) const;

	template <class T1>
	Image<T> concatenate(const Image<T1>& addImage) const;

	// function to separate the channels of the image
	template <class T1,class T2>
	void separate(unsigned firstNChannels,Image<T1>& image1,Image<T2>& image2) const;

	// function to sample patch
	template <class T1>
	void getPatch(Image<T1>& patch,double x,double y,int fsize) const;

	// function to crop the image
	template <class T1>
	void crop(Image<T1>& patch,int Lef,int Top,int Width,int Height) const;

	// basic numerics of images
	template <class T1,class T2>
	void Multiply(const Image<T1>& image1,const Image<T2>& image2);

	template <class T1,class T2,class T3>
	void Multiply(const Image<T1>& image1,const Image<T2>& image2,const Image<T3>& image3);

	template <class T1>
	void Multiplywith(const Image<T1>& image1);

	void Multiplywith(double value);

	template <class T1,class T2>
	void Add(const Image<T1>& image1,const Image<T2>& image2);

	template <class T1,class T2>
	void Add(const Image<T1>& image1,const Image<T2>& image2,double ratio);

	void Add(const T value);

	template <class T1>
	void Add(const Image<T1>& image1,const double value);

	template <class T1,class T2>
	void Subtract(const Image<T1>& image1,const Image<T2>& image2);

	// function to normalize an image
	void normalize(Image<T>& image);

	// function to compute the statistics of the image
	double norm2() const;

	template <class T1>
	double innerproduct(Image<T1>& image) const;

#ifdef MATLAB_FOUND
	template <class T1>
	void LoadMatlabImage(const mxArray* image);

	template <class T1>
	void ConvertFromMatlab(const T1* pMatlabPlane,int _width,int _height,int _nchannels);

	void OutputToMatlab(mxArray*& matrix);

	template <class T1>
	void ConvertToMatlab(T1* pMatlabPlane);
#endif
};


typedef Image<unsigned char> BiImage;
typedef Image<short int> IntImage;
typedef Image<float> FImage;
typedef Image<double> DImage;

//------------------------------------------------------------------------------------------
// constructor
//------------------------------------------------------------------------------------------
template <class T>
Image<T>::Image()
{
	pData=NULL;
	imWidth=imHeight=nChannels=nPixels=nElements=0;
	IsDerivativeImage=false;
}

//------------------------------------------------------------------------------------------
// constructor with specified dimensions
//------------------------------------------------------------------------------------------
template <class T>
Image<T>::Image(int width,int height,int nchannels)
{
	imWidth=width;
	imHeight=height;
	nChannels=nchannels;
	computeDimension();
	pData=NULL;
	pData=new T[nElements];
	if(nElements>0)
		memset(pData,0,sizeof(T)*nElements);
	IsDerivativeImage=false;
}

template <class T>
Image<T>::Image(const T& value,int _width,int _height,int _nchannels)
{
	pData=NULL;
	allocate(_width,_height,_nchannels);
	setValue(value);
}

#ifndef MATLAB_FOUND
template <class T>
Image<T>::Image(const QImage& image)
{
	pData=NULL;
	imread(image);
}
#endif

template <class T>
void Image<T>::allocate(int width,int height,int nchannels)
{
	clear();
	imWidth=width;
	imHeight=height;
	nChannels=nchannels;
	computeDimension();
	pData=NULL;
	pData=new T[nElements];
	if(nElements>0)
		memset(pData,0,sizeof(T)*nElements);
}

template <class T>
template <class T1>
void Image<T>::allocate(const Image<T1> &other)
{
	allocate(other.width(),other.height(),other.nchannels());
}

//------------------------------------------------------------------------------------------
// copy constructor
//------------------------------------------------------------------------------------------
template <class T>
Image<T>::Image(const Image<T>& other)
{
	pData=NULL;
	copyData(other);
}

//------------------------------------------------------------------------------------------
// destructor
//------------------------------------------------------------------------------------------
template <class T>
Image<T>::~Image()
{
	if(pData!=NULL)
		delete []pData;
}

//------------------------------------------------------------------------------------------
// clear the image
//------------------------------------------------------------------------------------------
template <class T>
void Image<T>::clear()
{
	if(pData!=NULL)
		delete []pData;
	pData=NULL;
	imWidth=imHeight=nChannels=nPixels=nElements=0;
}

//------------------------------------------------------------------------------------------
// reset the image (reset the buffer to zero)
//------------------------------------------------------------------------------------------
template <class T>
void Image<T>::reset()
{
	if(pData!=NULL)
		memset(pData,0,sizeof(T)*nElements);
}

template <class T>
void Image<T>::setValue(const T &value)
{
	for(int i=0;i<nElements;i++)
		pData[i]=value;
}

template <class T>
void Image<T>::setValue(const T& value,int _width,int _height,int _nchannels)
{
	if(imWidth!=_width || imHeight!=_height || nChannels!=_nchannels)
		allocate(_width,_height,_nchannels);
	setValue(value);
}

//------------------------------------------------------------------------------------------
// copy from other image
//------------------------------------------------------------------------------------------
template <class T>
void Image<T>::copyData(const Image<T>& other)
{
	imWidth=other.imWidth;
	imHeight=other.imHeight;
	nChannels=other.nChannels;
	nPixels=other.nPixels;
	IsDerivativeImage=other.IsDerivativeImage;

	if(nElements!=other.nElements)
	{
		nElements=other.nElements;		
		if(pData!=NULL)
			delete []pData;
		pData=NULL;
		pData=new T[nElements];
	}
	if(nElements>0)
		memcpy(pData,other.pData,sizeof(T)*nElements);
}

template <class T>
template <class T1>
void Image<T>::copy(const Image<T1>& other)
{
	clear();

	imWidth=other.width();
	imHeight=other.height();
	nChannels=other.nchannels();
	computeDimension();

	IsDerivativeImage=other.isDerivativeImage();

	pData=NULL;
	pData=new T[nElements];
	const T1*& srcData=other.data();
	for(int i=0;i<nElements;i++)
		pData[i]=srcData[i];
}

template <class T>
void Image<T>::im2double()
{
	if(IsFloat())
		for(int i=0;i<nElements;i++)
			pData[i]/=255;
}

//------------------------------------------------------------------------------------------
// override equal operator
//------------------------------------------------------------------------------------------
template <class T>
Image<T>& Image<T>::operator=(const Image<T>& other)
{
	copyData(other);
	return *this;
}

template <class T>
bool Image<T>::IsFloat() const
{
	if(typeid(T)==typeid(float) || typeid(T)==typeid(double) || typeid(T)==typeid(long double))
		return true;
	else
		return false;
}

template <class T>
template <class T1>
bool Image<T>::matchDimension(const Image<T1>& image) const
{
	if(imWidth==image.width() && imHeight==image.height() && nChannels==image.nchannels())
		return true;
	else
		return false;
}

//------------------------------------------------------------------------------------------
// function to move this image to a dest image at (x,y) with specified width and height
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Image<T>::moveto(Image<T1>& image,int x0,int y0,int width,int height)
{
	if(width==0)
		width=imWidth;
	if(height==0)
		height=imHeight;
	int NChannels=__min(nChannels,image.nchannels());

	int x,y;
	for(int i=0;i<height;i++)
	{
		y=y0+i;
		if(y>=image.height())
			break;
		for(int j=0;j<width;j++)
		{
			x=x0+j;
			if(x>=image.width())
				break;
			for(int k=0;k<NChannels;k++)
				image.data()[(y*image.width()+x)*image.nchannels()+k]=pData[(i*imWidth+j)*nChannels+k];
		}
	}
}


//------------------------------------------------------------------------------------------
// resize the image
//------------------------------------------------------------------------------------------
template <class T>
bool Image<T>::imresize(double ratio)
{
	if(pData==NULL)
		return false;

	T* pDstData;
	int DstWidth,DstHeight;
	DstWidth=(double)imWidth*ratio;
	DstHeight=(double)imHeight*ratio;
	pDstData=new T[DstWidth*DstHeight*nChannels];

	ImageProcessing::ResizeImage(pData,pDstData,imWidth,imHeight,nChannels,ratio);

	delete []pData;
	pData=pDstData;
	imWidth=DstWidth;
	imHeight=DstHeight;
	computeDimension();
	return true;
}

template <class T>
template <class T1>
void Image<T>::imresize(Image<T1>& result,double ratio)
{
	int DstWidth,DstHeight;
	DstWidth=(double)imWidth*ratio;
	DstHeight=(double)imHeight*ratio;
	if(result.width()!=DstWidth || result.height()!=DstHeight || result.nchannels()!=nChannels)
		result.allocate(DstWidth,DstHeight,nChannels);
	ImageProcessing::ResizeImage(pData,result.data(),imWidth,imHeight,nChannels,ratio);
}

template <class T>
void Image<T>::imresize(int dstWidth,int dstHeight)
{
	DImage foo(dstWidth,dstHeight,nChannels);
	ImageProcessing::ResizeImage(pData,foo.data(),imWidth,imHeight,nChannels,dstWidth,dstHeight);
	copyData(foo);
}

//------------------------------------------------------------------------------------------
// function to load the image
//------------------------------------------------------------------------------------------
#ifndef MATLAB_FOUND
template <class T>
bool Image<T>::imread(const QString &filename)
{
	clear();
	if(ImageIO::loadImage(filename,pData,imWidth,imHeight,nChannels))
	{
		computeDimension();
		return true;
	}
	return false;
}

template <class T>
void Image<T>::imread(const QImage& image)
{
	clear();
	ImageIO::loadImage(image,pData,imWidth,imHeight,nChannels);
	computeDimension();
}

//------------------------------------------------------------------------------------------
// function to write the image
//------------------------------------------------------------------------------------------
template <class T>
bool Image<T>::imwrite(const QString& filename,int quality) const
{
	ImageIO::ImageType type;
	if(IsDerivativeImage)
		type=ImageIO::derivative;
	else
		type=ImageIO::standard;

	return ImageIO::writeImage(filename,(const T*&)pData,imWidth,imHeight,nChannels,type,quality);
}

template <class T>
bool Image<T>::imwrite(const QString &filename, ImageIO::ImageType imagetype, int quality) const
{
	return ImageIO::writeImage(filename,(const T*&)pData,imWidth,imHeight,nChannels,imagetype,quality);
}
#endif

//------------------------------------------------------------------------------------------
// function to get x-derivative of the image
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Image<T>::dx(Image<T1>& result,bool IsAdvancedFilter) const
{
	if(matchDimension(result)==false)
		result.allocate(imWidth,imHeight,nChannels);
	result.reset();
	result.setDerivative();
	T1*& data=result.data();
	int i,j,k,offset;
	if(IsAdvancedFilter==false)
		for(i=0;i<imHeight;i++)
			for(j=0;j<imWidth-1;j++)
			{
				offset=i*imWidth+j;
				for(k=0;k<nChannels;k++)
					data[offset*nChannels+k]=(T1)pData[(offset+1)*nChannels+k]-pData[offset*nChannels+k];
			}
	else
	{
		double xFilter[5]={1,-8,0,8,-1};
		for(i=0;i<5;i++)
			xFilter[i]/=12;
		ImageProcessing::hfiltering(pData,data,imWidth,imHeight,nChannels,xFilter,2);
	}
}

template <class T>
template <class T1>
Image<T1> Image<T>::dx(bool IsAdvancedFilter) const
{
	Image<T1> result;
	dx<T1>(result,IsAdvancedFilter);
	return result;
}

//------------------------------------------------------------------------------------------
// function to get y-derivative of the image
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Image<T>::dy(Image<T1>& result,bool IsAdvancedFilter) const
{
	if(matchDimension(result)==false)
		result.allocate(imWidth,imHeight,nChannels);
	result.setDerivative();
	T1*& data=result.data();
	int i,j,k,offset;
	if(IsAdvancedFilter==false)
		for(i=0;i<imHeight-1;i++)
			for(j=0;j<imWidth;j++)
			{
				offset=i*imWidth+j;
				for(k=0;k<nChannels;k++)
					data[offset*nChannels+k]=(T1)pData[(offset+imWidth)*nChannels+k]-pData[offset*nChannels+k];
			}
	else
	{
		double yFilter[5]={1,-8,0,8,-1};
		for(i=0;i<5;i++)
			yFilter[i]/=12;
		ImageProcessing::vfiltering(pData,data,imWidth,imHeight,nChannels,yFilter,2);
	}
}

template <class T>
template <class T1>
Image<T1> Image<T>::dy(bool IsAdvancedFilter) const
{
	Image<T1> result;
	dy<T1>(result,IsAdvancedFilter);
	return result;
}

//------------------------------------------------------------------------------------------
// function to do Gaussian smoothing
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Image<T>::GaussianSmoothing(Image<T1>& image,double sigma,int fsize) const 
{
	Image<T1> foo;
	// constructing the 1D gaussian filter
	double* gFilter;
	gFilter=new double[fsize*2+1];
	double sum=0;
	sigma=sigma*sigma*2;
	for(int i=-fsize;i<=fsize;i++)
	{
		gFilter[i+fsize]=exp(-(double)(i*i)/sigma);
		sum+=gFilter[i+fsize];
	}
	for(int i=0;i<2*fsize+1;i++)
		gFilter[i]/=sum;

	// apply filtering
	imfilter_hv(image,gFilter,fsize,gFilter,fsize);

	delete gFilter;
}

//------------------------------------------------------------------------------------------
// function to smooth the image using a simple 3x3 filter
// the filter is [1 factor 1]/(factor+2), applied horizontally and vertically
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Image<T>::smoothing(Image<T1>& image,double factor)
{
	// build 
	double filter2D[9]={1,0,1,0, 0, 0,1, 0,1};
	filter2D[1]=filter2D[3]=filter2D[5]=filter2D[7]=factor;
	filter2D[4]=factor*factor;
	for(int i=0;i<9;i++)
		filter2D[i]/=(factor+2)*(factor+2);

	if(matchDimension(image)==false)
		image.allocate(imWidth,imHeight,nChannels);
	imfilter<T1>(image,filter2D,1);
}

template <class T>
template <class T1>
Image<T1> Image<T>::smoothing(double factor)
{
	Image<T1> result;
	smoothing(result,factor);
	return result;
}

template <class T>
void Image<T>::smoothing(double factor)
{
	Image<T> result(imWidth,imHeight,nChannels);
	smoothing(result,factor);
	copyData(result);
}

//------------------------------------------------------------------------------------------
//	 function of image filtering
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Image<T>::imfilter(Image<T1>& image,double* filter,int fsize) const
{
	if(matchDimension(image)==false)
		image.allocate(imWidth,imHeight,nChannels);
	ImageProcessing::filtering(pData,image.data(),imWidth,imHeight,nChannels,filter,fsize);
}

template <class T>
template <class T1>
Image<T1> Image<T>::imfilter(double *filter, int fsize)
{
	Image<T1> result;
	imfilter(result,filter,fsize);
	return result;
}

template <class T>
template <class T1>
void Image<T>::imfilter_h(Image<T1>& image,double* filter,int fsize) const
{
	if(matchDimension(image)==false)
		image.allocate(imWidth,imHeight,nChannels);
	ImageProcessing::hfiltering(pData,image.data(),imWidth,imHeight,nChannels,filter,fsize);
}

template <class T>
template <class T1>
void Image<T>::imfilter_v(Image<T1>& image,double* filter,int fsize) const
{
	if(matchDimension(image)==false)
		image.allocate(imWidth,imHeight,nChannels);
	ImageProcessing::vfiltering(pData,image.data(),imWidth,imHeight,nChannels,filter,fsize);
}


template <class T>
template <class T1>
void Image<T>::imfilter_hv(Image<T1> &image, double *hfilter, int hfsize, double *vfilter, int vfsize) const
{
	if(matchDimension(image)==false)
		image.allocate(imWidth,imHeight,nChannels);
	T1* pTempBuffer;
	pTempBuffer=new T1[nElements];
	ImageProcessing::hfiltering(pData,pTempBuffer,imWidth,imHeight,nChannels,hfilter,hfsize);
	ImageProcessing::vfiltering(pTempBuffer,image.data(),imWidth,imHeight,nChannels,vfilter,vfsize);
    delete pTempBuffer;
}

//------------------------------------------------------------------------------------------
//	 function for desaturation
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Image<T>::desaturate(Image<T1> &image) const
{
	if(nChannels!=3)
	{
		collapse(image);
		return;
	}
	if(!(image.width()==imWidth && image.height()==imHeight && image.nChannels==1))
		image.allocate(imWidth,imHeight,1);
	T1* data=image.data();
	int offset;
	for(int i=0;i<nPixels;i++)
	{
		offset=i*3;
		data[i]=(double)pData[offset]*.299+pData[offset+1]*.587+pData[offset+2]*.114;
	}
}

template <class T>
template <class T1>
void Image<T>::collapse(Image<T1> &image) const
{
	if(!(image.width()==imWidth && image.height()==imHeight && image.nChannels==1))
		image.allocate(imWidth,imHeight,1);
	T1* data=image.data();
	int offset;
	double temp;
	for(int i=0;i<nPixels;i++)
	{
		offset=i*nChannels;
		temp=0;
		for(int j=0;j<nChannels;j++)
			temp+=pData[offset+j];
		data[i]=temp/nChannels;
	}
}

//------------------------------------------------------------------------------------------
//  function to concatenate two images
//------------------------------------------------------------------------------------------
template <class T>
template <class T1,class T2>
void Image<T>::concatenate(Image<T1> &destImage, const Image<T2> &addImage) const
{
	if(addImage.width()!=imWidth || addImage.height()!=imHeight)
	{
		destImage.copy(*this);
		return;
	}
	int extNChannels=nChannels+addImage.nchannels();
	if(destImage.width()!=imWidth || destImage.height()!=imHeight || destImage.nchannels()!=extNChannels)
		destImage.allocate(imWidth,imHeight,extNChannels);
	int offset;
	T1*& pDestData=destImage.data();
	const T2*& pAddData=addImage.data();
	for(int i=0;i<imHeight;i++)
		for(int j=0;j<imWidth;j++)
		{
			offset=i*imWidth+j;
			for(int k=0;k<nChannels;k++)
				pDestData[offset*extNChannels+k]=pData[offset*nChannels+k];
			for(int k=nChannels;k<extNChannels;k++)
				pDestData[offset*extNChannels+k]=pAddData[offset*addImage.nchannels()+k-nChannels];
		}
}

template <class T>
template <class T1>
Image<T> Image<T>::concatenate(const Image<T1> &addImage) const
{
	Image<T> destImage;
	concatenate(destImage,addImage);
	return destImage;
}

//------------------------------------------------------------------------------------------
// function to separate the image into two
//------------------------------------------------------------------------------------------
template <class T>
template <class T1,class T2>
void Image<T>::separate(unsigned int firstNChannels, Image<T1> &image1, Image<T2> &image2) const
{
	image1.IsDerivativeImage=IsDerivativeImage;
	image2.IsDerivativeImage=IsDerivativeImage;

	if(firstNChannels>=nChannels)
	{
		image1=*this;
		image2.allocate(imWidth,imHeight,0);
		return;
	}
	if(firstNChannels==0)
	{
		image1.allocate(imWidth,imHeight,0);
		image2=*this;
		return;
	}
	int secondNChannels=nChannels-firstNChannels;
	if(image1.width()!=imWidth || image1.height()!=imHeight || image1.nchannels()!=firstNChannels)
		image1.allocate(imWidth,imHeight,firstNChannels);
	if(image2.width()!=imWidth || image2.height()!=imHeight || image2.nchannels()!=secondNChannels)
		image2.allocate(imWidth,imHeight,secondNChannels);

	for(int i=0;i<imHeight;i++)
		for(int j=0;j<imWidth;j++)
		{
			int offset=i*imWidth+j;
			for(int k=0;k<firstNChannels;k++)
				image1.pData[offset*firstNChannels+k]=pData[offset*nChannels+k];
			for(int k=firstNChannels;k<nChannels;k++)
				image2.pData[offset*secondNChannels+k-firstNChannels]=pData[offset*nChannels+k];
		}
}

//------------------------------------------------------------------------------------------
// function to separate the image into two
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Image<T>::getPatch(Image<T1>& patch,double x,double y,int wsize) const
{
	int wlength=wsize*2+1;
	if(patch.width()!=wlength || patch.height()!=wlength || patch.nchannels()!=nChannels)
		patch.allocate(wlength,wlength,nChannels);
	else
		patch.reset();
	ImageProcessing::getPatch(pData,patch.data(),imWidth,imHeight,nChannels,x,y,wsize);
}

//------------------------------------------------------------------------------------------
// function to crop an image
//------------------------------------------------------------------------------------------
template <class T>
template <class T1>
void Image<T>::crop(Image<T1>& patch,int Left,int Top,int Width,int Height) const
{
	if(patch.width()!=Width || patch.height()!=Height || patch.nchannels()!=nChannels)
		patch.allocate(Width,Height,nChannels);
	// make sure that the cropping is valid
	if(Left<0 || Top<0 || Left>=imWidth || Top>=imHeight)
	{
		cout<<"The cropping coordinate is outside the image boundary!"<<endl;
		return;
	}
	if(Width<0 || Height<0 || Width+Left>imWidth || Height+Top>imHeight)
	{
		cout<<"The patch to crop is invalid!"<<endl;
		return;
	}
	ImageProcessing::cropImage(pData,imWidth,imHeight,nChannels,patch.data(),Left,Top,Width,Height);
}

//------------------------------------------------------------------------------------------
// function to multiply image1, image2 and image3 to the current image
//------------------------------------------------------------------------------------------
template <class T>
template <class T1,class T2,class T3>
void Image<T>::Multiply(const Image<T1>& image1,const Image<T2>& image2,const Image<T3>& image3)
{
	if(image1.matchDimension(image2)==false || image2.matchDimension(image3)==false)
	{
		cout<<"Error in image dimensions--function Image<T>::Multiply()!"<<endl;
		return;
	}
	if(matchDimension(image1)==false)
		allocate(image1);

	const T1*& pData1=image1.data();
	const T2*& pData2=image2.data();
	const T3*& pData3=image3.data();

	for(int i=0;i<nElements;i++)
		pData[i]=pData1[i]*pData2[i]*pData3[i];
}

template <class T>
template <class T1,class T2>
void Image<T>::Multiply(const Image<T1>& image1,const Image<T2>& image2)
{
	if(image1.matchDimension(image2)==false)
	{
		cout<<"Error in image dimensions--function Image<T>::Multiply()!"<<endl;
		return;
	}
	if(matchDimension(image1)==false)
		allocate(image1);

	const T1*& pData1=image1.data();
	const T2*& pData2=image2.data();

	for(int i=0;i<nElements;i++)
		pData[i]=pData1[i]*pData2[i];
}

template <class T>
template <class T1>
void Image<T>::Multiplywith(const Image<T1> &image1)
{
	if(matchDimension(image1)==false)
	{
		cout<<"Error in image dimensions--function Image<T>::Multiplywith()!"<<endl;
		return;
	}
	const T1*& pData1=image1.data();
	for(int i=0;i<nElements;i++)
		pData[i]*=pData1[i];
}

template <class T>
void Image<T>::Multiplywith(double value)
{
	for(int i=0;i<nElements;i++)
		pData[i]*=value;
}

//------------------------------------------------------------------------------------------
// function to add image2 to image1 to the current image
//------------------------------------------------------------------------------------------
template <class T>
template <class T1,class T2>
void Image<T>::Add(const Image<T1>& image1,const Image<T2>& image2)
{
	if(image1.matchDimension(image2)==false)
	{
		cout<<"Error in image dimensions--function Image<T>::Add()!"<<endl;
		return;
	}
	if(matchDimension(image1)==false)
		allocate(image1);

	const T1*& pData1=image1.data();
	const T2*& pData2=image2.data();
	for(int i=0;i<nElements;i++)
		pData[i]=pData1[i]+pData2[i];	
}

template <class T>
template <class T1,class T2>
void Image<T>::Add(const Image<T1>& image1,const Image<T2>& image2,double ratio)
{
	if(image1.matchDimension(image2)==false)
	{
		cout<<"Error in image dimensions--function Image<T>::Add()!"<<endl;
		return;
	}
	if(matchDimension(image1)==false)
		allocate(image1);

	const T1*& pData1=image1.data();
	const T2*& pData2=image2.data();
	for(int i=0;i<nElements;i++)
		pData[i]=pData1[i]+pData2[i]*ratio;	
}

template <class T>
template <class T1>
void Image<T>::Add(const Image<T1>& image1,const double ratio)
{
	if(matchDimension(image1)==false)
	{
		cout<<"Error in image dimensions--function Image<T>::Add()!"<<endl;
		return;
	}
	const T1*& pData1=image1.data();
	for(int i=0;i<nElements;i++)
		pData[i]+=pData1[i]*ratio;	
}

template <class T>
void Image<T>::Add(const T value)
{
	for(int i=0;i<nElements;i++)
		pData[i]+=value;
}

//------------------------------------------------------------------------------------------
// function to subtract image2 from image1
//------------------------------------------------------------------------------------------
template <class T>
template <class T1,class T2>
void Image<T>::Subtract(const Image<T1> &image1, const Image<T2> &image2)
{
	if(image1.matchDimension(image2)==false)
	{
		cout<<"Error in image dimensions--function Image<T>::Add()!"<<endl;
		return;
	}
	if(matchDimension(image1)==false)
		allocate(image1);

	const T1*& pData1=image1.data();
	const T2*& pData2=image2.data();
	for(int i=0;i<nElements;i++)
		pData[i]=pData1[i]-pData2[i];
}

//------------------------------------------------------------------------------------------
// normalize an image
//------------------------------------------------------------------------------------------
template <class T>
void Image<T>::normalize(Image<T>& image)
{
	if(image.width()!=imWidth || image.height()!=imHeight || image.nchannels()!=nChannels)
		image.allocate(imWidth,imHeight,nChannels);
	T Max,Min;
	Max=Min=pData[0];
	for(int i=0;i<nElements;i++)
	{
		Max=qMax(Max,pData[i]);
		Min=qMin(Min,pData[i]);
	}
	if(Max==Min)
		return;
	double ratio=1/(Max-Min);
	if(IsFloat()==false)
		ratio*=255;
	T* data=image.data();
	for(int i=0;i<nElements;i++)
		data[i]=(double)(pData[i]-Min)*ratio;
}

template <class T>
double Image<T>::norm2() const
{
	double result=0;
	for(int i=0;i<nElements;i++)
		result+=pData[i]*pData[i];
	return result;
}

template <class T>
template <class T1>
double Image<T>::innerproduct(Image<T1> &image) const
{
	double result=0;
	const T1* pData1=image.data();
	for(int i=0;i<nElements;i++)
		result+=pData[i]*pData1[i];
	return result;
}

#ifdef MATLAB_FOUND

template <class T>
template <class T1>
void Image<T>::LoadMatlabImage(const mxArray *image)
{
	int nDim = mxGetNumberOfDimensions(image);
	const int* imDim = mxGetDimensions(image);
	if(nDim==2)
		allocate(imDim[1],imDim[0]);
	else if(nDim==3)
		allocate(imDim[1],imDim[0],imDim[2]);
	else
		mexErrMsgTxt("The image doesn't have the appropriate dimension!");
	T1* pMatlabPlane=(T1*)mxGetData(image);
	bool IsMatlabFloat;
	if(typeid(T1)==typeid(float) || typeid(T1)==typeid(double) || typeid(T1)==typeid(long double))
		IsMatlabFloat=true;
	else
		IsMatlabFloat=false;
	bool isfloat=IsFloat();
	if(isfloat==IsMatlabFloat)
	{
		ConvertFromMatlab<T1>(pMatlabPlane,imWidth,imHeight,nChannels);
		return;
	}
	int offset=0;
	if(isfloat==true)
		for(int i=0;i<imHeight;i++)
			for(int j=0;j<imWidth;j++)
				for(int k=0;k<nChannels;k++)
					pData[offset++]=(double)pMatlabPlane[k*nPixels+j*imHeight+i]/255;
	else
		for(int i=0;i<imHeight;i++)
			for(int j=0;j<imWidth;j++)
				for(int k=0;k<nChannels;k++)
					pData[offset++]=(double)pMatlabPlane[k*nPixels+j*imHeight+i]*255;
}

template <class T>
template <class T1>
void Image<T>::ConvertFromMatlab(const T1 *pMatlabPlane, int _width, int _height, int _nchannels)
{
	if(imWidth!=_width || imHeight!=_height || nChannels!=_nchannels)
		allocate(_width,_height,_nchannels);
	int offset=0;
	for(int i=0;i<imHeight;i++)
		for(int j=0;j<imWidth;j++)
			for(int k=0;k<nChannels;k++)
				pData[offset++]=pMatlabPlane[k*nPixels+j*imHeight+i];
}

// convert image data to matlab matrix
template <class T>
template <class T1>
void Image<T>::ConvertToMatlab(T1 *pMatlabPlane)
{
	int offset=0;
	for(int i=0;i<imHeight;i++)
		for(int j=0;j<imWidth;j++)
			for(int k=0;k<nChannels;k++)
				pMatlabPlane[k*nPixels+j*imHeight+i]=pData[offset++];
}

template <class T>
void Image<T>::OutputToMatlab(mxArray *&matrix)
{
	long int dims[3];
	dims[0]=imHeight;
	dims[1]=imWidth;
	dims[2]=nChannels;
	if(nChannels==1)
		matrix=mxCreateNumericArray(2, dims,mxDOUBLE_CLASS, mxREAL);
	else
		matrix=mxCreateNumericArray(3, dims,mxDOUBLE_CLASS, mxREAL);
	ConvertToMatlab<double>((double*)mxGetData(matrix));
}

#endif


#endif
