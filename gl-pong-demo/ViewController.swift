//
//  ViewController.swift
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-03-23.
//

import GLKit

extension ViewController: GLKViewControllerDelegate {
    // Updates scene each frame
    func glkViewControllerUpdate(_ controller: GLKViewController) {
        scene.update()
    }
}

class ViewController: GLKViewController {
    private var context: EAGLContext?
    private var scene: Scene!
    
    private func setupGLView() {
        context = EAGLContext(api: .openGLES3)
        EAGLContext.setCurrent(context)
        
        if let view = self.view as? GLKView, let context = context {
            view.context = context
            delegate = (self as GLKViewControllerDelegate)
            
            scene = Scene()
            scene.setup(view)
            scene.loadModels()
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupGLView()
        
        let panGesture = UIPanGestureRecognizer(target: self, action: #selector(self.doPan(_:)))
        view.addGestureRecognizer(panGesture)
    }
    
    // Renders the scene each frame
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        scene.draw()
    }
    
    @objc func doPan(_ sender: UIPanGestureRecognizer) {
        let changedDistance = sender.translation(in: view)
        
        if changedDistance.x > 25 {
            scene.playerPaddleXInput = Float(changedDistance.x)
            print("x -> ", changedDistance.x)
            sender.setTranslation(.zero, in: view)
            sender.reset()
        }
        
        if changedDistance.x < -25 {
            scene.playerPaddleXInput = Float(changedDistance.x)
            print("x -> ", changedDistance.x)
            sender.setTranslation(.zero, in: view)
            sender.reset()
        }
        
        // Reset the x displacement once the gesture ends
        if sender.state == .ended {
            scene.playerPaddleXInput = 0.0
        }
    }
}
