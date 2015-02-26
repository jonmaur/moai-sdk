namespace Moai
{
	class MoaiHost
	{
	public:
		MoaiHost();
		~MoaiHost();

		void Init(int width, int height, int dpi);
		void Render();
		void RedetectGraphicsContext();
		void Update();
		void Finalize();

		void Pause(bool paused);

		
	};
}