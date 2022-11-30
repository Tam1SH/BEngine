import React from 'react';
import './App.css';

function Header() {
	return (
		<>
			<header className='Header' style={{
				position: 'fixed',
				zIndex: '1',
			}}>
			</header>
			<div style={{
				width: '100%',
				height: '50px',
			}}>

			</div>
		</>
	)
}

function SideBarSection() {
	return (
		<details style={{
		}}>
			<summary></summary>
			<summary style={{
				marginLeft: '15px',
			}}></summary>
		</details>
	)
}

function SideBar() {
	return (
		<article className='SideBar' style={{
			height: 'calc(100vh - 50px)',
			width: '100%',
			minWidth: '250px',
			position: 'sticky',
			top : '50px',
			zIndex: '1',
			maxWidth: '400px',
			padding: '15px',
			boxSizing: 'border-box',
		}}>
			<div style={{
				height: '100%',
				width: '100%',
			}}>
				<SideBarSection />
			</div>
		</article>
	)
}

function Content() {
	return (
		<>
			<article className='TopPanel'>
				<div className='TopPanelElement' style={{
					width: '35px',
					height: '35px',
					background: 'blue',
				}}>

				</div>
				<div className='TopPanelElement' style={{
					width: '35px',
					height: '35px',
					background: 'red',
				}}>

				</div>
				<div className='TopPanelElement' style={{
					width: '35px',
					height: '35px',
					background: 'green',
				}}>

				</div>
				<div className='TopPanelElement' style={{
					width: '35px',
					height: '35px',
					background: 'blue',
				}}>

				</div>
			</article>
			<article style={{
				height: '100%',
				width: '100%',
				minWidth: '600px',
				flexDirection: 'column',
				padding: '20px',
			}}>

				<div style={{
					background: 'red',
					border: '1px white solid',
					width: '500px',
					height: '500px',
				}}></div>
				<div style={{
					background: 'red',
					border: '1px white solid',
					width: '500px',
					height: '500px',
				}}></div>
				<div style={{
					background: 'red',
					border: '1px white solid',
					width: '500px',
					height: '500px',
				}}></div>
				<div style={{
					background: 'red',
					border: '1px white solid',
					width: '500px',
					height: '500px',
				}}></div>

			</article>
		</>
	)
}

function MainBody() {
	return (


		<div className='MainBody'>
			<SideBar />
			<Content />
		</div>
	)
}

function App() {
	return (
		<>
			<Header />
			<MainBody />
			<footer>
			</footer>
		</>
	);
}

export default App;

