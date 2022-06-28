#include "stdafx.h"
#include "platform.hpp"
#include "AbstractRender.hpp"
#include "RenderBuffer.hpp"
#include "IRenderData.hpp"

using BE_STD::shared_ptr;
using BE_STD::optional;

namespace BEbraEngine {

	enum class RenderBufferPoolUsage {
		//Создаёт представления одного буфера.
		SeparateOneBuffer

	};

	template<typename RenderData>
	class IRenderBufferPool {

	public:

		virtual ~IRenderBufferPool() { }

		/// <summary>
		/// Выделяет память.
		/// </summary>
		/// <param name="count">: Количество представлений, которое может предоставить пул.</param>
		/// <param name="sizeofData">: Размер куска памяти, предоставленное каждому представлению.</param>
		/// <param name="type">: Тип буфера.</param>
		virtual void allocate(uint32_t count, uint32_t sizeofData, AbstractRender::TypeBuffer type) = 0;

		virtual void deallocate(uint32_t count) = 0;

		/// <summary>
		/// Обнуляет часть буфера.
		/// </summary>
		/// <param name="count">: количество ячеек, которые будут обнулены в буфере</param>
		/// <param name="offset">: смещение по количеству ячеек</param>
		virtual void reset(size_t count, size_t offset) = 0;

		/// <summary>
		/// Копирует массив в буфер, заданный через bindData(), в момент обновления данных предназначенных для отрисовки.
		/// </summary>
		virtual void map() = 0;

		/// <summary>
		/// задаёт количество элементов, которые будут скопированы в буфер.
		/// </summary>
		virtual void setCountToMap(size_t count) = 0;

		virtual void free(shared_ptr<RenderBufferView> view) = 0;

		virtual void setContext(AbstractRender* render) = 0;

		virtual void bindData(const vector<RenderData>& data) = 0;

		virtual shared_ptr<RenderBuffer> getBuffer() = 0;

		virtual void setUsage(RenderBufferPoolUsage usage) = 0;

		virtual size_t getCount() = 0;

		/// <summary>
		/// возращает часть буфера, имеющее смещение от начала буфера, а также ограниченную длину, заданную при вызове allocate().
		/// </summary>
		virtual optional<shared_ptr<RenderBufferView>> get() = 0;
	};

}