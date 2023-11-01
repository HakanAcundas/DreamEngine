#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer2D.h"
#include <iostream>

namespace dream { namespace graphics {

	// Data that goes into Shader
	struct RenderableData
	{
		glm::vec3 Position;
		glm::vec2 TextureCoord;
		float TextureID;
		glm::vec4 Color;
	};

	struct RendererData
	{
		Buffer* Buffer;
		VertexArray* VertexArray;
		IndexBuffer* IndexBuffer;
		std::vector<unsigned int> TextureSlots;
		RenderableData* RenderableData = nullptr;
		uint32_t RenderableIndexCount;

		struct CameraData
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
	};

	static RendererData r_Data;
	Renderer2D *Renderer2D::singleton = nullptr;

	void Renderer2D::Init()
	{
		r_Data.RenderableIndexCount = 0;
		r_Data.VertexArray = new VertexArray();
		r_Data.Buffer = new Buffer(RENDERER_BUFFER_SIZE);
		r_Data.Buffer->AddBufferElement("shader_TexCoord", ShaderDataType::Float, 2);
		r_Data.Buffer->AddBufferElement("shader_TexIndex", ShaderDataType::Float, 1);
		r_Data.Buffer->AddBufferElement("shader_Color", ShaderDataType::Float, 4);
		r_Data.Buffer->AddBufferElement("shader_Position", ShaderDataType::Float, 3);
		r_Data.Buffer->CalculateStride();
		
		r_Data.VertexArray->AddBuffer(r_Data.Buffer);

		unsigned int* quadIndices = new unsigned int[RENDERER_INDICES_SIZE];
		unsigned int offset = 0;
		for (unsigned int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		r_Data.IndexBuffer = new IndexBuffer(quadIndices, RENDERER_INDICES_SIZE);
		r_Data.VertexArray->SetIndexBuffer(r_Data.IndexBuffer);
		r_Data.VertexArray->Unbind();
	}

	void Renderer2D::Begin()
	{
		r_Data.Buffer->Bind();
		r_Data.RenderableData = (RenderableData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		r_Data.Buffer->Unbind();
	}

	// TO DO convert this function into DrawQuad (its is already converted but make a base 
	// function to apply different variations of DrawQuad. Example DrawRotatedQuad etc...
	void Renderer2D::DrawRenderable(const glm::vec2& position, const glm::vec2& size, const Texture2D* texture, const glm::vec4& color)
	{
		/*glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });*/

		// Texture Information
		glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const unsigned int tid = texture->GetTID();

		float ts = 0.0f;
		if (tid > 0)
		{
			bool found = false;
			// Search for texture ID
			for (int i = 0; i < r_Data.TextureSlots.size(); i++)
			{
				if (r_Data.TextureSlots[i] == tid)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				// If the texture slots are full
				if (r_Data.TextureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				// Else add the new texture ID to a slot
				r_Data.TextureSlots.push_back(tid);
				ts = (float)(r_Data.TextureSlots.size());
			}
		}

		r_Data.RenderableData->Position = glm::vec3(position.x, position.y, 0);
		r_Data.RenderableData->Color = color;
		r_Data.RenderableData->TextureCoord = textureCoords[0];
		r_Data.RenderableData->TextureID = ts;
		r_Data.RenderableData++;
		
		r_Data.RenderableData->Position = glm::vec3(position.x, position.y + size.y, 0);
		r_Data.RenderableData->Color = color;
		r_Data.RenderableData->TextureCoord = textureCoords[1];
		r_Data.RenderableData->TextureID = ts;
		r_Data.RenderableData++;
		
		r_Data.RenderableData->Position = glm::vec3(position.x + size.x, position.y + size.y, 0);
		r_Data.RenderableData->Color = color;
		r_Data.RenderableData->TextureCoord = textureCoords[2];
		r_Data.RenderableData->TextureID = ts;
		r_Data.RenderableData++;
		
		r_Data.RenderableData->Position = glm::vec3(position.x + size.x, position.y, 0);
		r_Data.RenderableData->Color = color;
		r_Data.RenderableData->TextureCoord = textureCoords[3];
		r_Data.RenderableData->TextureID = ts;
		r_Data.RenderableData++;
		
		r_Data.RenderableIndexCount += 6;
	}

	void Renderer2D::DrawRenderable(const glm::vec2& position, const glm::vec2& size, const unsigned int tid, const glm::vec4& color)
	{
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0))
		//	* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		// Texture Information
		glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		float ts = 0.0f;

		if (tid > 0)
		{
			bool found = false;
			// Search for texture ID
			for (int i = 0; i < r_Data.TextureSlots.size(); i++)
			{
				if (r_Data.TextureSlots[i] == tid)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				// If the texture slots are full
				if (r_Data.TextureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				// Else add the new texture ID to a slot
				r_Data.TextureSlots.push_back(tid);
				ts = (float)(r_Data.TextureSlots.size());
			}
		}

		r_Data.RenderableData->Position = glm::vec3(position.x, position.y, 1);
		r_Data.RenderableData->Color = color;
		r_Data.RenderableData->TextureCoord = textureCoords[0];
		r_Data.RenderableData->TextureID = ts;
		r_Data.RenderableData++;
		
		r_Data.RenderableData->Position = glm::vec3(position.x, position.y + size.y, 1);
		r_Data.RenderableData->Color = color;
		r_Data.RenderableData->TextureCoord = textureCoords[1];
		r_Data.RenderableData->TextureID = ts;
		r_Data.RenderableData++;
		
		r_Data.RenderableData->Position = glm::vec3(position.x + size.x, position.y + size.y, 1);
		r_Data.RenderableData->Color = color;
		r_Data.RenderableData->TextureCoord = textureCoords[2];
		r_Data.RenderableData->TextureID = ts;
		r_Data.RenderableData++;
		
		r_Data.RenderableData->Position = glm::vec3(position.x + size.x, position.y, 1);
		r_Data.RenderableData->Color = color;
		r_Data.RenderableData->TextureCoord = textureCoords[3];
		r_Data.RenderableData->TextureID = ts;
		r_Data.RenderableData++;
		
		r_Data.RenderableIndexCount += 6;
	}

	void Renderer2D::Flush()
	{
		for (int i = 0; i < r_Data.TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, r_Data.TextureSlots[i]);
		}

		r_Data.VertexArray->Bind();
		r_Data.IndexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, r_Data.RenderableIndexCount, GL_UNSIGNED_INT, NULL);
		r_Data.IndexBuffer->Unbind();
		r_Data.VertexArray->Unbind();
		
		r_Data.RenderableIndexCount = 0;
	}
}}