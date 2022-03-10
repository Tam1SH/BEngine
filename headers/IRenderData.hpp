#pragma once
namespace BEbraEngine {

	class IRenderData {
	public:
		virtual ~IRenderData() {}
		/// <summary>
		/// ¬озращает указатель на данные, которые будут использоватьс€ в шейдере. 
		/// ¬ыделенна€ пам€ть под указатель извне не освобождаетс€.
		/// </summary>
		virtual const void* getData() noexcept { return 0; }
		virtual size_t getDataSize() const noexcept { return 0; }
	};
}