#include "OpenglPrograms.h"

void OpenglPrograms::setPN(GLuint program)
{
	dsPN = program;
}

void OpenglPrograms::setPNTxDS(GLuint program)
{
	dsPNTxDS = program;
}

void OpenglPrograms::setPNTxD(GLuint program)
{
	dsPNTxD = program;
}

GLuint OpenglPrograms::dsPN = 0;
GLuint OpenglPrograms::dsPNTxDS = 0;
GLuint OpenglPrograms::dsPNTxD = 0;