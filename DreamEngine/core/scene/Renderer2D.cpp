#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer2D.h"
#include <iostream>

namespace dream { namespace graphics {

	static RendererData r_Data;
	Renderer2D *Renderer2D::singleton = nullptr;

	void Renderer2D::Init()
	{
		FT_Library ft;

		if (FT_Init_FreeType(&ft))
		{
			std::cout << "Failed to compile FreeType: " << std::endl << &ft << std::endl;
		}

		r_Data.textureCoords[0] = { 0.0f, 0.0f };
		r_Data.textureCoords[1] = { 1.0f, 0.0f };
		r_Data.textureCoords[2] = { 1.0f, 1.0f };
		r_Data.textureCoords[3] = { 0.0f, 1.0f };

		r_Data.renderableVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		r_Data.renderableVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		r_Data.renderableVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		r_Data.renderableVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		r_Data.renderableIndexCount = 0;
		r_Data.vertexArray = new VertexArray();
		r_Data.buffer = new Buffer(RENDERER_BUFFER_SIZE);

		// The order of the buffer-elements must be the same as the vertex-shader layout order
		r_Data.buffer->AddBufferElement("shader_Position", ShaderDataType::Float, 3);
		r_Data.buffer->AddBufferElement("shader_TexCoord", ShaderDataType::Float, 2);
		r_Data.buffer->AddBufferElement("shader_TextureID", ShaderDataType::Float, 1);
		r_Data.buffer->AddBufferElement("shader_Color", ShaderDataType::Float, 4);
		r_Data.buffer->CalculateStride();
		
		r_Data.vertexArray->AddBuffer(r_Data.buffer);

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

		r_Data.indexBuffer = new IndexBuffer(quadIndices, RENDERER_INDICES_SIZE);
		r_Data.vertexArray->SetIndexBuffer(r_Data.indexBuffer);
		r_Data.vertexArray->Unbind();
	}

	void Renderer2D::Begin()
	{
		r_Data.buffer->Bind();
		r_Data.renderableData = (RenderableData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		r_Data.buffer->Unbind();
	}

	float Renderer2D::SubmitTexture(const Texture2D* texture)
	{
		const unsigned int tid = texture->GetTID();
		float ts = 0.0f;
		if (tid > 0)
		{
			bool found = false;
			// Search for texture ID
			for (int i = 0; i < r_Data.textureSlots.size(); i++)
			{
				if (r_Data.textureSlots[i] == tid)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				// If the texture slots are full
				if (r_Data.textureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				// Else add the new texture ID to a slot
				r_Data.textureSlots.push_back(tid);
				ts = (float)(r_Data.textureSlots.size());
			}
		}

		return ts;
	}

	// TO DO convert this function into DrawQuad (its is already converted but make a base 
	// function to apply different variations of DrawQuad. Example DrawRotatedQuad etc...
	void Renderer2D::DrawRenderable(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < 4; i++)
		{
			r_Data.renderableData->position = transform * r_Data.renderableVertexPositions[i];
			r_Data.renderableData->color = color;
			r_Data.renderableData->textureCoord = r_Data.textureCoords[i];
			r_Data.renderableData->textureID = 0;
			r_Data.renderableData++;
		}

		r_Data.renderableIndexCount += 6;
	}

	void Renderer2D::DrawRenderable(const glm::vec2& position, const glm::vec2& size, const Texture2D* texture, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		float ts = 0;
		if (texture != NULL)
			ts = SubmitTexture(texture);

		for (int i = 0; i < 4; i++)
		{
			r_Data.renderableData->position = transform * r_Data.renderableVertexPositions[i];
			r_Data.renderableData->color = color;
			r_Data.renderableData->textureCoord = r_Data.textureCoords[i];
			r_Data.renderableData->textureID = ts;
			r_Data.renderableData++;
		}
		
		r_Data.renderableIndexCount += 6;
	}

	void Renderer2D::DrawLabel(const std::string& text, float x, float y, const glm::vec4& color)
	{
		
	}

	void Renderer2D::Flush()
	{
		for (int i = 0; i < r_Data.textureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, r_Data.textureSlots[i]);
		}

		r_Data.vertexArray->Bind();
		r_Data.indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, r_Data.renderableIndexCount, GL_UNSIGNED_INT, NULL);
		r_Data.indexBuffer->Unbind();
		r_Data.vertexArray->Unbind();
		
		r_Data.renderableIndexCount = 0;
	}
}}
