#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer2D.h"
#include <iostream>

namespace dream { namespace graphics {

	struct RendererData
	{
		struct CameraData
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
	};

	static RendererData r_Data;
	Renderer2D* Renderer2D::renderer2d = nullptr;

	Renderer2D::Renderer2D()
	{
		Init();
	}

	void Renderer2D::Init()
	{
		m_RenderableIndexCount = 0;
		
		m_VertexArray = new VertexArray();
		m_Buffer = new Buffer(RENDERER_BUFFER_SIZE);
		m_Buffer->AddBufferElement("shader_TexCoord", ShaderDataType::Float, 2);
		m_Buffer->AddBufferElement("shader_TexIndex", ShaderDataType::Float, 1);
		m_Buffer->AddBufferElement("shader_Color", ShaderDataType::Float, 4);
		m_Buffer->AddBufferElement("shader_Position", ShaderDataType::Float, 3);
		m_Buffer->CalculateStride();
		
		m_VertexArray->AddBuffer(m_Buffer);

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

		m_IndexBuffer = new IndexBuffer(quadIndices, RENDERER_INDICES_SIZE);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_VertexArray->Unbind();
	}

	void Renderer2D::Begin()
	{
		m_Buffer->Bind();
		m_RenderableData = (RenderableData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		m_Buffer->Unbind();
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
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == tid)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				// If the texture slots are full
				if (m_TextureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				// Else add the new texture ID to a slot
				m_TextureSlots.push_back(tid);
				ts = (float)(m_TextureSlots.size());
			}
		}

		m_RenderableData->Position = glm::vec3(position.x, position.y, 0);
		m_RenderableData->Color = color;
		m_RenderableData->TextureCoord = textureCoords[0];
		m_RenderableData->TextureID = ts;
		m_RenderableData++;

		m_RenderableData->Position = glm::vec3(position.x, position.y + size.y, 0);
		m_RenderableData->Color = color;
		m_RenderableData->TextureCoord = textureCoords[1];
		m_RenderableData->TextureID = ts;
		m_RenderableData++;

		m_RenderableData->Position = glm::vec3(position.x + size.x, position.y + size.y, 0);
		m_RenderableData->Color = color;
		m_RenderableData->TextureCoord = textureCoords[2];
		m_RenderableData->TextureID = ts;
		m_RenderableData++;

		m_RenderableData->Position = glm::vec3(position.x + size.x, position.y, 0);
		m_RenderableData->Color = color;
		m_RenderableData->TextureCoord = textureCoords[3];
		m_RenderableData->TextureID = ts;
		m_RenderableData++;

		m_RenderableIndexCount += 6;
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
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == tid)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				// If the texture slots are full
				if (m_TextureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				// Else add the new texture ID to a slot
				m_TextureSlots.push_back(tid);
				ts = (float)(m_TextureSlots.size());
			}
		}

		m_RenderableData->Position = glm::vec3(position.x, position.y, 1);
		m_RenderableData->Color = color;
		m_RenderableData->TextureCoord = textureCoords[0];
		m_RenderableData->TextureID = ts;
		m_RenderableData++;

		m_RenderableData->Position = glm::vec3(position.x, position.y + size.y, 1);
		m_RenderableData->Color = color;
		m_RenderableData->TextureCoord = textureCoords[1];
		m_RenderableData->TextureID = ts;
		m_RenderableData++;

		m_RenderableData->Position = glm::vec3(position.x + size.x, position.y + size.y, 1);
		m_RenderableData->Color = color;
		m_RenderableData->TextureCoord = textureCoords[2];
		m_RenderableData->TextureID = ts;
		m_RenderableData++;

		m_RenderableData->Position = glm::vec3(position.x + size.x, position.y, 1);
		m_RenderableData->Color = color;
		m_RenderableData->TextureCoord = textureCoords[3];
		m_RenderableData->TextureID = ts;
		m_RenderableData++;

		m_RenderableIndexCount += 6;
	}

	void Renderer2D::Flush()
	{
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		m_VertexArray->Bind();
		m_IndexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, m_RenderableIndexCount, GL_UNSIGNED_INT, NULL);
		m_IndexBuffer->Unbind();
		m_VertexArray->Unbind();

		m_RenderableIndexCount = 0;
	}
}}