using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BirdScript : MonoBehaviour
{
    public Rigidbody2D myRigidbody;
    public float flapStrength;
    public LogicScript logic;
    public bool birdIsAlive = true;
    public float upLimit = 13f;
    public float downLimit = -13f;
        [SerializeField] private float _yBound;

    [SerializeField] private Rigidbody2D _rigidbody;


    // Start is called before the first frame update
    void Start()
    {
        logic = GameObject.FindGameObjectWithTag("Logic").GetComponent<LogicScript>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space) && birdIsAlive)
        {
            myRigidbody.velocity = Vector2.up * flapStrength;
        }

        // Then check if the bird is out of bounds
        if (_rigidbody.position.y > upLimit || _rigidbody.position.y < _yBound)
        {
            Debug.Log("Bird out of bounds");
            birdIsAlive = false;
            logic.gameOver();
        }

    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        logic.gameOver();
        birdIsAlive = false;
    }
}
